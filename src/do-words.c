#ifndef __DO_WORDS_H_
#define __DO_WORDS_H_

#include "do-words.h"
#include "eg-result.h"

#define BUFFER_SIZE 100

bool end_of_line(Line ln) { 
    return ln.end_of_line ||  (ln.range.beg < ln.range.end && *ln.range.beg == '\n'); 
}

//
int range_len(Range r) { return r.end - r.beg; }
bool range_is_empty(Range r) { return r.end <= r.beg || *r.beg == '\n'; }
bool range_has_next(Range r) { return r.end > r.beg && *r.beg != '\n'; }

bool subrange_has_word(Range r, char* end) {
    return r.end < end && (isspace(*r.end) || *r.end == '\0');
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
                    if (lam.value) { 
                        Result* lam_res = lam.value;
                        if(lam_res-> err) {
                            return;
                        }
                    }
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
