#ifndef __HASH_H_
#define __HASH_H_

#include "word-freqs.h"

typedef struct {
    unsigned int v;
    Word k;
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
} LimitedHashMap ;


unsigned long hash(unsigned char *str);
Entry* get(LimitedHashMap* m, Word k) ;

#endif
