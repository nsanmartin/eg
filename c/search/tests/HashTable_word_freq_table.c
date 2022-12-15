#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string-hash-table.h>

#define INITSZ 40

int testHashTable_cmp_by_freq(const void* p, const void* q) {
    const Entry* x = p;
    const Entry* y = q;
    const intptr_t xcount = (intptr_t) x->value;
    const intptr_t ycount = (intptr_t) y->value;
    return xcount - ycount;
}

int testHashTable_table_add_symbol(HashTable* t, char* word) {
    Entry* e = hashTableSearch(t, word);
    if (!e) 
        return hashTableGetError();
    e->value = (void*) 1+(intptr_t)e->value;
    return 0;
}

int testHashTable_count_words (HashTable* symbols, FILE* fp) {
    unsigned long nlines = 0;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    const char* delimiters = " \t\n";

    while ((read = getline(&line, &len, fp)) != -1) {
        char* token = strtok(line, delimiters);
        while(token) {
            int error = testHashTable_table_add_symbol(symbols, token);
            if (error) {
                return error;
            }
            token = strtok(NULL, delimiters);
        }
        nlines++;
    }
    fclose(fp);

    return 0;
}


int main (int argc, char ** argv) {

    if (argc != 2)
        printf("Uso: %s FILE [FILE ...]\n", argv[0]);

    HashTable symbols;
    hashTableInit(&symbols, INITSZ);

    FILE *fp;
    char* filename = argv[1];
    if ((fp = fopen(filename, "r"))) {

        int error = testHashTable_count_words(&symbols, fp);
        if (error) {
            fprintf(stderr, "error counting words in %s: %s\n",
                    filename, hashTableErrToString(error));
            return error;
        }

        // qsort(symbols.table, symbols.size, sizeof(Entry), testHashTable_cmp_by_freq);

        for (int i = 0; i < symbols.size; ++i) {
            Entry e = symbols.table[i];
            intptr_t count = (intptr_t)e.value;

            if (count) {
                printf("%s: %ld\n", e.key, count);
            }
        }
    } else {
        fprintf(stderr, "Error opening file '%s'.\n", filename);
    }

    return 0;
}

