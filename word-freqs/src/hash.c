// https://stackoverflow.com/questions/7666509/hash-function-for-string
#include "hash.h"

unsigned long
hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


Entry* get(LimitedHashMap* m, Word k) {
    if (k.size == 0 || k.cstr == NULL) {
        fprintf(stderr, "Error: null key\n");
        exit(1);
    }

    unsigned int h = hash(k.cstr) % m->size;
    unsigned int nmovs = 0;
    while (true) {
        Entry* rv =  &m->table[h];
        if (rv->k.cstr == NULL) {
            if (++m->inserts > m->size * 8 / 10) {
                fprintf(stderr, "Too many keys for map!\n");
                exit(1);
            }
            char* mem = malloc(k.size);
            if (mem == NULL) {
                fprintf(stderr, "Memory error!\n");
                exit(1);
            }
            rv->k.cstr = mem;
            rv->k.size = k.size;
            strcpy(rv->k.cstr, k.cstr);
            if(nmovs > m->stats.max_move) { m->stats.max_move = nmovs; }
            return rv;
        } else if (word_eq(rv->k, k)) {
            return rv;
        }
        h = (h + 1) % m->size;
        ++m->stats.moves;
        nmovs++;
    }
}
