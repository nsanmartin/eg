#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
 
char * skip_space_or_null(char* beg, char* end) ;

#define BUFFER_SIZE 80000

#define NOTSPACE 0
#define SPACE 1

typedef struct {
    char* beg;
    char* end;
} Range;

typedef struct {
    Range range;
    bool end_of_line;
} Line;


int range_len(Range r) { return r.end - r.beg; }

bool is_incomplete_line(Range r, int size) { return r.end == r.beg + size; }


bool range_is_empty(Range r) { return r.end <= r.beg || *r.beg == '\n'; }
bool range_has_next(Range r) { return r.end > r.beg && *r.beg != '\n'; }
bool subrange_has_word(Range r, char* end) { return r.end < end && (isspace(*r.end) || *r.end == '\0'); }
bool range_is_eol(Range r) { return r.beg < r.end && *r.beg == '\n'; }
bool end_of_line(Line ln) { 
    return ln.end_of_line ||  (ln.range.beg < ln.range.end && *ln.range.beg == '\n'); 
}

char* first_not_space(Range r) {
    char* rv = r.beg;
    while(rv < r.end && !isspace(*rv)) { ++rv; }
    return rv;
}

Range range_get_next_word(Range r) {
    while (range_has_next(r)  && (isspace(*r.beg) || *r.beg == '\0')) { ++r.beg; }
    r.end = first_not_space(r);
    return r;
}


int copy_range(Range r, char* dest) {
    int size = r.end - r.beg - 1;
    for(int i = 0; i < size ; ++i) {
        dest[i] = r.beg[i];
    }
    return size;
}

//TODO: do a WordStream reader such as the read version

int main(void)
{
    char buf[BUFFER_SIZE];

    int outer = 0;
    int inner = 0;

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
        
                    *w.end = '\0';
                    printf("%s\n", w.beg); 
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
