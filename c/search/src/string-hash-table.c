#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "string-hash-table.h"


// https://stackoverflow.com/questions/7666509/hash-function-for-string

unsigned long hash(const char *str)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


Entry* search(HashTable* m, const char* k) {
    if (k == NULL) {
        fprintf(stderr, "Error: null key\n");
        return NULL;
    }

    unsigned int h = hash(k) % m->size;
    unsigned int nmovs = 0;
    while (true) {
        Entry* rv =  &m->table[h];
        if (rv->key == NULL) {
            if (++m->inserts > m->size * 8 / 10) {
                //todo increase size
                fprintf(stderr, "Too many keys for map!\n");
                exit(1);
            }
            rv->key = strdup(k);
            if (rv->key == NULL) {
                fprintf(stderr, "Memory error!\n");
                return NULL;
            }
            return rv;
        } else if (strcmp(rv->key, k) == 0) {
            return rv;
        }
        h = (h + 1) % m->size;
        //++m->stats.moves;
        nmovs++;
    }
    return NULL;
}

int hashTableInit(HashTable* t, unsigned long nhashes) {
    Entry* entries = calloc(nhashes, sizeof (Entry));
    if (!entries) 
        return -1;

    *t = (HashTable){
        .table = entries, .size = nhashes, .inserts = 0
    };
    return 0;
}
