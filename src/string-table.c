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
string_hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


void stringTableGet(StringTable* m, Str k, Result* res) {
    if (k.len == 0 || k.cstr == NULL) {
        fprintf(stderr, "Error: null key\n");
        res->err = true;
        return;
    }

    unsigned int h = string_hash(k.cstr) % m->size;
    unsigned int nmovs = 0;
    while (true) {

        Entry* e = &m->table[h];
        if (e->k.cstr == NULL) {
            if (++m->inserts > m->size * 65 / 100) {
                fprintf(stderr, "Too many keys for map!\n");
                res->err = true;
                return;
            }

            Result r_copy = { .ok = &e->k, .err = false };
            strCopy(k, &r_copy);
            if (r_copy.err) {
                fprintf(stderr, "Memory error!\n");
                res->err = true;
                return;
            }
            if(nmovs > m->stats.max_move) { m->stats.max_move = nmovs; }
            res->ok = e;
            res->err = false;
            return;
        } else if (strEq(e->k, k)) {
            res->ok = e;
            res->err = false;
            return;
        }
        h = (h + 7) % m->size;
        ++m->stats.moves;
        nmovs++;
    }
}
