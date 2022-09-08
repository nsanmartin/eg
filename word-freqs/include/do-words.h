#ifndef __DO_WORDS_
#define __DO_WORDS_

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>


typedef struct {
    char* beg;
    char* end;
} Range;

typedef struct {
    Range range;
    bool end_of_line;
} Line;

typedef struct Lambda Lambda;

struct Lambda {
    void* ctx;
    void (*app) (Lambda, Range);
};


void do_words(FILE* stream, Lambda lam)  ;

inline bool end_of_line(Line ln) { 
    return ln.end_of_line ||  (ln.range.beg < ln.range.end && *ln.range.beg == '\n'); 
}


inline int range_len(Range r) { return r.end - r.beg; }
inline bool range_is_empty(Range r) { return r.end <= r.beg || *r.beg == '\n'; }
inline bool range_has_next(Range r) { return r.end > r.beg && *r.beg != '\n'; }
inline bool subrange_has_word(Range r, char* end) {
    return r.end < end && (isspace(*r.end) || *r.end == '\0');
}
inline char* first_not_space(Range r) {
    char* rv = r.beg;
    while(rv < r.end && !isspace(*rv)) { ++rv; }
    return rv;
}

inline Range range_get_next_word(Range r) {
    while (range_has_next(r)  && (isspace(*r.beg) || *r.beg == '\0')) { ++r.beg; }
    r.end = first_not_space(r);
    return r;
}
inline int copy_range(Range r, char* dest) {
    int size = r.end - r.beg - 1;
    for(int i = 0; i < size ; ++i) {
        dest[i] = r.beg[i];
    }
    return size;
}
#endif
