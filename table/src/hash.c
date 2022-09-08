// https://stackoverflow.com/questions/7666509/hash-function-for-string
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hash.h"

#define TABLE_INITIAL_SIZE 100


//Str strOfCstr(char* cstr, size_t len) {
//    Str rv = { .cstr = cstr, .len = len };
//    return rv;
//}

bool strEq(Str x, Str y) { return x.len == y.len && strcmp(x.cstr, y.cstr) == 0; }
//Str newStr(char* cstr) {
//
//}

StringTable newStringTable() {
    StringTable rv = malloc(sizeof (StringTable));
    Entry* table = malloc(TABLE_INITIAL_SIZE * (sizeof (Entry)));

    struct StringTableData t = {
        .table = table, .size = TABLE_INITIAL_SIZE, .inserts = 0, .stats ={0}
    };
    *rv = t;
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


Entry* get(StringTable m, Str k) {
    if (k.len == 0 || k.cstr == NULL) {
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
            char* mem = malloc(k.len);
            if (mem == NULL) {
                fprintf(stderr, "Memory error!\n");
                exit(1);
            }
            rv->k.cstr = mem;
            rv->k.len = k.len;
            strcpy(rv->k.cstr, k.cstr);
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
