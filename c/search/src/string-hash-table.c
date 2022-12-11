#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "string-hash-table.h"


// https://stackoverflow.com/questions/7666509/hash-function-for-string

Entry* hashTableSearch(HashTable* m, const char* k);

unsigned long hash(const char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int hashTableDuplicate(HashTable* t) {
    Entry* entries = t->table;
    unsigned long size = t->size;

    int error = hashTableInit(t, size + size);
    if (error) {
        fprintf(stderr, "error duplicating hash table");
        return -1;
    }

    for (int i = 0; i < size; ++i) {
        Entry e = entries[i];
        if (e.key) {
            Entry* ep = hashTableSearch(t, e.key);
            if (ep) {
                ep->value = e.value;
            } else {
                fprintf(stderr, "error duplicating hash table");
                return -1;
            }
        }
    }
    free(entries);
    return 0;
}


Entry* hashTableSearch(HashTable* m, const char* k) {
    if (k == NULL) {
        fprintf(stderr, "Error: null key\n");
        return NULL;
    }

    unsigned int h = hash(k) % m->size;
    unsigned int nmovs = 0;
    while (true) {
        Entry* rv =  &m->table[h];
        if (rv->key == NULL) {
            if (m->inserts > m->size * 8 / 10) {
                int error = hashTableDuplicate(m);
                nmovs = 0;
                h = hash(k) % m->size;
                if (error) 
                    return NULL;
                continue;
            }
            rv->key = strdup(k);
            if (rv->key == NULL) {
                fprintf(stderr, "Memory error!\n");
                return NULL;
            }
            ++m->inserts;
            return rv;
        } else if (strcmp(rv->key, k) == 0) {
            return rv;
        }
        h = (h + 1) % m->size;
        nmovs++;
        if (nmovs > m->size) {
            int error = hashTableDuplicate(m);
            if (error) 
                return NULL;
            nmovs = 0;
            h = hash(k) % m->size;
        }
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
