//TODO: fix this
#include <string.h>
#include "word-freqs.h"
#include "hash.h"
#include <limits.h>

#define BUFFER_SIZE 80000
#define NHASHES 60000


int main () {
    char buffer[BUFFER_SIZE];
    const unsigned long nhashes = NHASHES;
    Entry entries[NHASHES] = {{0}};
    
    LimitedHashMap map = { .table = entries, .size = nhashes, .inserts = 0 };
    WordStream ws = make_word_stream(STDIN_FILENO, buffer, BUFFER_SIZE);


    while (ws.status == HasNext) {
        Word w = get_next_word(&ws);
        Entry* e = get(&map, w);
        e->v++;
    }

    for (int i = 0; i < map.size; ++i) {
        Entry e = map.table[i];
        if (e.k.cstr != NULL) {
            printf("%s: %d\n", e.k.cstr, e.v);
        }
    }
}


