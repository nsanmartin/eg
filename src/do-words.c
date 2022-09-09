#ifndef __DO_WORDS_H_
#define __DO_WORDS_H_

#include "do-words.h"

#define BUFFER_SIZE 100

void do_words(FILE* stream, Lambda lam)  {
    char buf[BUFFER_SIZE];
    Line ln = { .range = { .beg = buf, .end = buf + BUFFER_SIZE}, .end_of_line = false };
    for ( ; fgets(ln.range.beg, range_len(ln.range), stdin) != NULL; ) {
        ln.range.beg = buf;
        ln.end_of_line = false;
        Range w = {.beg = 0, .end = 0};
        while (!ln.end_of_line && range_has_next(ln.range)) {
            w = range_get_next_word(ln.range);
            if(subrange_has_word(w, ln.range.end)) {
                if (range_has_next(w)) {
                    ln.end_of_line = *w.end == '\n';
                    lam.app(lam, &w);
                }
            }
            ln.range.beg = w.end;
        }
        int ncopied = 0;
        if (!end_of_line(ln) && range_has_next(w)) {
            ncopied = copy_range(w, buf);
            ln.range.beg = buf + ncopied;
            ln.range.end = buf + BUFFER_SIZE - ncopied;
        }
        ln.range.beg = buf + ncopied;
        ln.range.end = buf + BUFFER_SIZE - ncopied;
    }
}

#endif
