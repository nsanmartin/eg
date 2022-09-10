// https://stackoverflow.com/questions/7666509/hash-function-for-string
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "string-table.h"


#include "lambda.h"
#include "eg-result.h"
#include "eg-str.h"


StringTable stringTableWithSize(size_t size) {
    Entry* table = malloc(size * (sizeof (Entry)));

    StringTable rv = {
        .table = table, .size = size, .inserts = 0, .stats ={0}
    };
    return rv;

}

unsigned long
hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


Entry* stringTableGet(StringTable* m, Str k) {
    if (k.len == 0 || k.cstr == NULL) {
        fprintf(stderr, "Error: null key\n");
        exit(1);
    }

    unsigned int h = hash(k.cstr) % m->size;
    unsigned int nmovs = 0;
    while (true) {
        Entry* rv =  &m->table[h];
        if (rv->k.cstr == NULL) {
            if (++m->inserts > m->size * 65 / 100) {
                fprintf(stderr, "Too many keys for map!\n");
                exit(1);
            }

            Result r = { .ok = &rv->k, .err = false };
            strCopy(k, r);
            if (r.err) {
                fprintf(stderr, "Memory error!\n");
                exit(1);
            }
            if(nmovs > m->stats.max_move) { m->stats.max_move = nmovs; }
            return rv;
        } else if (strEq(rv->k, k)) {
            return rv;
        }
        h = (h + 1) % m->size;
        ++m->stats.moves;
        nmovs++;
    }
}
