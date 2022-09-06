#include <string.h>
#include "word-freqs.h"
#include "hash.h"
#include <limits.h>

#define BUFFER_SIZE 800000
#define NHASHES (BUFFER_SIZE >> 2)

typedef struct {
    unsigned int v;
    Word k;
} Entry;

typedef struct {
    Entry* table;
    unsigned long size;
    size_t inserts;
} LimitedHashMap ;

bool word_eq(Word v, Word w) { return v.size == w.size && strcmp(v.cstr, w.cstr) == 0; }

Entry* get(LimitedHashMap* m, Word k) {
    if (k.size == 0 || k.cstr == NULL) {
        fprintf(stderr, "Error: null key\n");
        exit(1);
    }

    unsigned int h = hash(k.cstr) % m->size;
    while (true) {
        Entry* rv =  &m->table[h];
        if (rv->k.cstr == NULL) {
            if (++m->inserts > m->size * 8 / 10) {
                fprintf(stderr, "Too many keys for map!\n");
                exit(1);
            }
            char* mem = malloc(k.size);
            if (mem == NULL) {
                fprintf(stderr, "Memory error!\n");
                exit(1);
            }
            rv->k.cstr = mem;
            rv->k.size = k.size;
            strcpy(rv->k.cstr, k.cstr);
            return rv;
        } else if (word_eq(rv->k, k)) {
            return rv;
        }
        h = (h + 1) % m->size;
    }
}


int main () {
    char buffer[BUFFER_SIZE];
    const unsigned long nhashes = BUFFER_SIZE >> 2;
    unsigned long hashes[NHASHES] = {0};
    Entry entries[NHASHES] = {{0}};
    
    LimitedHashMap map = { .table = entries, .size = BUFFER_SIZE>>2, .inserts = 0 };
    WordStream ws = make_word_stream(STDIN_FILENO, buffer, BUFFER_SIZE);

    unsigned long minhash = ULONG_MAX;
    unsigned long maxhash = 0;

    while (ws.status == HasNext) {
        Word w = get_next_word(&ws);
        Entry* e = get(&map, w);
        e->v++;
    }

    for (int i = 0; i < NHASHES; ++i) {
        Entry e = map.table[i];
        if (e.k.cstr != NULL) {
            printf("%s: %d\n", e.k.cstr, e.v);
        }
    }
}


