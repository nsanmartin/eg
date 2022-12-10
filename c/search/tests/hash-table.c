#include <stdio.h>
#include "string-hash-table.h"



int main () {
    HashTable table;
    hashTableInit(&table, 30);

    Entry* e;
    e = search(&table, "hello");
    if (!e) {
        printf("error searching hello\n");
    } else {
        e->value = (void*) 1;
    }

    e = search(&table, "world");
    if (!e) {
        printf("error searching world\n");
    } else {
        e->value = (void*) 1;
    }


    e = search(&table, "hello world");
    if (!e) {
        printf("error searching hello world\n");
    } else {
        printf("hello world search: %p\n", e->value);
    }

    e = search(&table, "hello");
    if (!e) {
        printf("error searching hello\n");
    } else {
        printf("hello search: %p\n", e->value);
    }
}
