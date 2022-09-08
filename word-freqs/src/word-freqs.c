#include "word-freqs.h"
#include <assert.h>


int range_len(Range r) { return r.end - r.beg; }

bool word_eq(Word v, Word w) { return v.size == w.size && strcmp(v.cstr, w.cstr) == 0; }

Word word_from_range(Range r) {
    *r.end = '\0';
    Word rv = { .cstr = r.beg, .size = range_len(r) };
    return rv;
}

// Range methods

//bool range_is_empty(Range r) { return r.beg  >= r.end; }
bool range_is_empty(Range r) { return r.end <= r.beg || *r.beg == '\n'; }

char * skip_space_or_null(char* beg, char* end) {
    char* rv = beg;
    while(beg < end && (isspace(*rv) || *rv == '\0')) {
        ++rv;
    }
    return rv;
}


char* range_move_skip_word(Range* r) {
    while(!range_is_empty(*r) &&  !isspace(*r->beg) ) {
        ++r->beg;
    }
    return r->beg;
}



// buffer methods

Buffer empty_buffer_from_array(char* arr, int size) {
    Buffer rv = {
        .data = arr,
        .size = size,
        .readable = { .beg = arr, .end = arr},
        .incomplete_word = { .beg = arr, .end = arr}
    };
    return rv;
}

bool buffer_is_empty(Buffer b) { return b.readable.beg >= b.readable.end; }

bool buffer_has_incomplete_word(Buffer b) { return !range_is_empty(b.incomplete_word); }

Word buffer_read_next_word(Buffer* b) {
    char* word_beg = b->readable.beg;
    char* word_end = range_move_skip_word(&b->readable);
    //*word_end = '\0';

    // if this is false we reach the end of the range and should leave it empty
    if(b->readable.beg < b->readable.end) {
        ++b->readable.beg;
    }
    Word rv = { .cstr = word_beg, .size = word_end - word_beg };
    return rv;
}

void print_word_too_large_for_buffer_msg(Buffer b, const char* func_name) {
    int wordlen = (int)(b.incomplete_word.end - b.incomplete_word.beg); // cast safe ensured by buffer size
    fprintf(stderr, "%s: word to large for buffer size!\n", func_name);
    fprintf(stderr, "buffer size: %d \n", b.size);
    fprintf(stderr, "buffer content:\n");
    fprintf(stderr, "'%.*s'\n", b.size, b.data);
}


// WordStream methods
char* move_incomplete_word_to_beginning(WordStream* ws) {
    const int len = range_len(ws->buffer.incomplete_word);
    int i = 0;
    for (; i < len; ++i) {
        ws->buffer.data[i] = ws->buffer.incomplete_word.beg[i];
    }
    return ws->buffer.data + i;
}

 StreamStatus get_stream_status(WordStream s, int nread, int size) {
    if (!buffer_is_empty(s.buffer)) {
        return HasNext;
    } else if (!s.file_read) {
        return HasNext;
    }
    return End;
}

Range get_incomplete_word(char* beg, char* end) {
   Range rv = { .beg = end, .end = end };
   while (beg < rv.end && !isspace(*rv.beg)) { --rv.beg; }
   if (*rv.beg == ' ') { ++ rv.beg; }
   return rv;
}

void fill_buffer_with_stream(WordStream* ws) {
    assert(buffer_is_empty(ws->buffer));
    assert(!ws->file_read);

    while(buffer_is_empty(ws->buffer) && !ws->file_read) {
        char* read_beg = ws->buffer.data;
        if (buffer_has_incomplete_word(ws->buffer)) {
            read_beg = move_incomplete_word_to_beginning(ws);
        }

        const int size = ws->buffer.size - (read_beg - ws->buffer.data);
        const int nread = read(ws->fd, read_beg, size);

        if (nread < 0) {
            fprintf(stderr, "error reading file!");
            ws->status = Error;
        }

        if (nread < size) { ws->file_read = true; }

        if (nread >= 0) {
            char* read_end = read_beg + nread;

            ws->buffer.incomplete_word = get_incomplete_word(read_beg, read_beg + nread);

            if (read_beg == ws->buffer.incomplete_word.beg
                    && !range_is_empty(ws->buffer.incomplete_word)) {
                print_word_too_large_for_buffer_msg(ws->buffer, __FUNCTION__);
                ws->status = Error;
                return;
            }

            ws->buffer.readable.beg = skip_space_or_null(ws->buffer.data, read_beg + nread);
            ws->buffer.readable.end = ws->buffer.incomplete_word.beg;

            ws->status = get_stream_status(*ws, nread, size);
        }
    }
}



Word get_next_word(WordStream* ws) {

    if (ws->next.size == 0) {
        while (!ws->file_read && buffer_is_empty(ws->buffer) && ws->status != Error) {
            fill_buffer_with_stream(ws);
        }

        if (!buffer_is_empty(ws->buffer)) {
            ws->next = buffer_read_next_word(&ws->buffer);
            ws->buffer.readable.beg = skip_space_or_null(ws->buffer.readable.beg, ws->buffer.readable.end);
            if (ws->file_read && range_is_empty(ws->buffer.readable)) {
                ws->status = End;
            }
        } else {
            if (range_is_empty(ws->buffer.incomplete_word)) {
                ws->status = End;
            }
        }
    }

    char* w = ws->next.cstr;
    int wsize = ws->next.size;

    // word consumed so its gone
    ws->next.size = 0;
    //ws->status = Empty;
    Word rv = { .cstr = w, .size = wsize };
    rv.cstr[rv.size] = '\0';
    return rv;
}


 WordStream make_word_stream(int fd, char* arr, int size) {
    WordStream ws = {
        .fd = fd,
        .buffer = empty_buffer_from_array(arr, size),
        .next = { arr, 0 },
        .status = Empty,
        .file_read = false
    };

    do {
        fill_buffer_with_stream(&ws);
    }
    while (buffer_is_empty(ws.buffer) && ws.status == HasNext);
    return ws;
}

