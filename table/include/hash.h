#ifndef __HASH_H_
#define __HASH_H_

#include <stddef.h>

#define LEN(arr) (sizeof(arr)/sizeof(arr[0]))

typedef struct {
    char* cstr;
    int len;
} Str;


typedef struct {
    unsigned int v;
    Str k;
} Entry;

typedef struct {
    long moves;
    long max_move;
} TableStats;

typedef struct StringTableData {
    Entry* table;
    unsigned long size;
    size_t inserts;
    TableStats stats;
}* StringTable;


unsigned long hash(unsigned char *str);
StringTable newStringTable() ;
Entry* get(StringTable m, Str k) ;

#define strFromLit(CSTR) ({ Str rv = { .cstr = CSTR, .len = LEN(CSTR) }; rv; })

#endif
