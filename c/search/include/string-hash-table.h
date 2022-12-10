#ifndef __STRING_HASH_TABLE_
#define __STRING_HASH_TABLE_

#include <stddef.h>

typedef struct {
    void* value;
    const char* key;
} Entry;

typedef struct {
    Entry* table;
    unsigned long size;
    size_t inserts;
} HashTable;


unsigned long hash(const char *str);
Entry* search(HashTable* m, const char* k) ;
int hashTableInit(HashTable* t, unsigned long nhashes);

#endif


