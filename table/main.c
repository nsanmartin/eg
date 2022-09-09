#include <stdio.h>
#include "hash.h"
#include "../word-freqs/include/do-words.h"

Str strFromRange(Range r) {
    *r.end = '\0';
    Str rv = { .cstr = r.beg, .len = range_len(r) };
    return rv;
}

//void table_entries_debug(StringTable t) {
//    for (int i = 0; i < t->size; ++i) {
//        Entry e = t->table[i];
//        if (e.k.cstr != NULL) {
//            printf("%s -> %d\n", e.k.cstr, e.v);
//        }
//    }
//}

void lam_print(Lambda lam, Range r) {
    *r.end = '\0';
    printf("%s\n", r.beg); 

    Entry* e = get(lam.ctx, strFromRange(r));
    //e->v++;
}

int main() {
    StringTable table = newStringTable();
    //char cstr[] = "a string";
    //Str s = strFromLit(cstr);
    //Entry* e = get(table, s);
    //e->v = 7;

    //get(table, strFromLit("lala")) -> v = 9;
    ////e->v = 9;
    //table_entries_debug(table);
    Lambda lambda = { .ctx = table, .app = &lam_print };
    do_words(stdin, lambda);
}
