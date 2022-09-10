#include <stdio.h>
#include "string-table.h"
#include "do-words.h"
#include "eg-result.h"

#define TABLE_INITIAL_SIZE 10000

Str strFromRange(Range r) {
    *r.end = '\0';
    Str rv = { .cstr = r.beg, .len = range_len(r) };
    return rv;
}

void table_entries_debug(StringTable t) {
    for (int i = 0; i < t.size; ++i) {
        Entry e = t.table[i];
        if (e.k.cstr != NULL) {
            printf("%s -> %d\n", e.k.cstr, e.v);
        }
    }
}

void table_stats_debug(StringTable t) {
    printf("size: %ld\n", t.size);
    printf("inserts: %ld\n", t.inserts);
    printf("moves: %ld\n", t.stats.moves);
    printf("max_move: %ld\n", t.stats.max_move);
}

void lam_print(Lambda* lam, void* arg) {
    Range r = GET_POINTED_VALUE(Range, arg);
    *r.end = '\0';
    //printf("%s\n", r.beg); 

    Result res;
    stringTableGet(lam->ctx, strFromRange(r), &res);
    Entry* e = res.ok;
    e->v++;

    SET_POINTED_VALUE(lam->value, res);
}

int main() {
    StringTable table = stringTableWithSize(TABLE_INITIAL_SIZE);
    Result lam_res = {0};
    Lambda lambda = { .ctx = &table, .app = &lam_print, .value = &lam_res};
    do_words(stdin, &lambda);
    //table_entries_debug(table);
    table_stats_debug(table);
    if (POINTED(Result, lambda.value).err) {
        fprintf(stderr, "Error too many keys! for map size\n");
    }
}
