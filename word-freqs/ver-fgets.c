#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "word-freqs.h"
#include "do-words.h"
 
char * skip_space_or_null(char* beg, char* end) ;

#define NHASHES 50

#define NOTSPACE 0
#define SPACE 1


bool is_incomplete_line(Range r, int size) { return r.end == r.beg + size; }


bool range_is_eol(Range r) { return r.beg < r.end && *r.beg == '\n'; }


//TODO: do a WordStream reader such as the read version

void lam_print_range(Lambda* lam, void* arg) {
    Range r = GET_POINTED_VALUE(Range, arg);
    *r.end = '\0';
    printf("%s\n", r.beg); 
    LimitedHashMap* map = (LimitedHashMap*) lam->ctx;
    Entry* e = get(map, word_from_range(r));
    e->v++;
}

int main(void)
{

    const unsigned long nhashes = NHASHES;
    
    Entry* entries = malloc(sizeof (Entry) * nhashes);
    LimitedHashMap map = { .table = entries, .size = nhashes, .inserts = 0, .stats = {0} };


    Lambda lambda = { .ctx = &map, .app = &lam_print_range };

    do_words(stdin, &lambda);


    for (int i = 0; i < map.size; ++i) {
        Entry e = map.table[i];
        if (e.k.cstr != NULL) {
            printf("%s: %d\n", e.k.cstr, e.v);
        }
    }


    //fprintf(stderr, "inserts: %ld\n", map.inserts);
    //fprintf(stderr, "movs: %ld\n", map.stats.moves);
    //fprintf(stderr, "max move: %ld\n", map.stats.max_move);
}
