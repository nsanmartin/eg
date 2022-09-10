#ifndef __HASH_H_
#define __HASH_H_

#include <stddef.h>
#include "eg-str.h"

#define LEN(arr) (sizeof(arr)/sizeof(arr[0]))


typedef struct {
    unsigned int v;
    Str k;
} Entry;

typedef struct {
    long moves;
    long max_move;
} TableStats;

typedef struct {
    Entry* table;
    unsigned long size;
    size_t inserts;
    TableStats stats;
} StringTable;


unsigned long hash(unsigned char *str);
StringTable stringTableWithSize(size_t size) ;
Entry* stringTableGet(StringTable* m, Str k) ;


#endif
