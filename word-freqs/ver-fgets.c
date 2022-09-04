#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
 
char * skip_space_or_null(char* beg, char* end) ;

#define BUFFER_SIZE 80000

#define NOTSPACE 0
#define SPACE 1

typedef struct {
    char* newline;
    char* last[2];
} Line;

typedef struct {
    char* beg;
    char* end;
} Range;

int range_len(Range r) { return r.end - r.beg; }

bool is_incomplete_line(Range r, int size) { return r.end == r.beg + size; }


bool range_is_empty(Range r) { return r.end <= r.beg || *r.beg == '\n'; }
bool range_has_next(Range r) { return r.end > r.beg && *r.beg != '\n'; }
bool subrange_has_word(Range r, char* end) { return r.end < end && (isspace(*r.end) || *r.end == '\0'); }
bool range_is_eol(Range r) { return r.beg < r.end && *r.beg == '\n'; }

char* first_not_space(Range r) {
    char* rv = r.beg;
    while(rv < r.end && !isspace(*rv)) { ++rv; }
    return rv;
}

Range get_next_word(Range r) {
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

int main(void)
{
    char buf[BUFFER_SIZE];

    int outer = 0;
    int inner = 0;
    Range visible = { .beg = buf, .end = buf + BUFFER_SIZE };

    for ( ; fgets(visible.beg, range_len(visible), stdin) != NULL; ) {
        visible.beg = buf;
        Range w = {.beg = 0, .end = 0};
        while (range_has_next(visible)) {
            w = get_next_word(visible);
            visible.beg = w.end;
            if(subrange_has_word(w, visible.end)) {
                if (range_has_next(w)) {
                    *w.end = '\0';
                    //printf("%s\n", w.beg);
                    printf("%.*s\n", (int)(w.end - w.beg), w.beg); 
                }
            }
        }

        int ncopied = 0;
        if (!range_is_eol(visible) && range_has_next(w)) {
            ncopied = copy_range(w, buf);
            visible.beg = buf + ncopied;
            visible.end = buf + BUFFER_SIZE - ncopied;
        }

        visible.beg = buf + ncopied;
        visible.end = buf + BUFFER_SIZE - ncopied;
    }
}
