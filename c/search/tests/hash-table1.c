#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include "string-hash-table.h"

#define LEN(A) (sizeof(A)/sizeof(*A))

const char* strs[] =
    { "hello"
    , "world"
    , "hello world"
    };

int main () {
    HashTable table;
    hashTableInit(&table, 30);

    Entry* e;
    for (int i = 0; i < LEN(strs); ++i) {
        const char* s = strs[i];
        printf("inserting %s\n", s);
        e = search(&table, s);
        if (!e) {
            printf("error searching '%s'\n", s);
        } else {
            void* v = e->value;
            e->value = (void*) 1;
            assert(v == NULL);
        }
    }

    for (int i = 0; i < LEN(strs); ++i) {
        const char* s = strs[i];
        e = search(&table,s);
        if (!e) {
            printf("error searching '%s'\n",s);
        } else {
            printf("'%s' search: %p\n", s, e->value);
            assert((intptr_t)e->value == 1);
        }
    }

    printf("inserts: %ld\n", table.inserts);
    assert(table.inserts == LEN(strs));
   
}
