#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>



typedef struct {
    int count;
    char* key;
} Entry;

typedef struct {
    intptr_t sz;
    intptr_t cap;
    Entry* entries;
} VecEntry;


int cmp_by_freq(const void* p, const void* q) {
    const Entry* x = p;
    const Entry* y = q;
    return x->count - y->count;
}

int table_init(VecEntry* v, int initial_capacity) {
    Entry* entries = malloc(initial_capacity * sizeof(Entry));
    if (!entries) {
        fprintf(stderr, "table_init: Not memory\n");
        return -1;
    }
    *v = (VecEntry){
        .sz = 0,
        .cap = initial_capacity,
        .entries = entries
    };
    int initial_htable_size = 1 + ((v->cap * 5) / 4);
    int error = hcreate(initial_htable_size) == 0;
    if (error) {
        fprintf(stderr, "table_init: hcreate error\n");
    }
    return error;
}

Entry* table_get(const VecEntry* v, int i) {
    if (i >= v->sz) {
        return NULL;
    }
    return &v->entries[i];
}


int table_duplicate(VecEntry* table) {
    table->cap *= 2;
    table->entries = realloc(table->entries, table->cap * sizeof(Entry));
    if (!table->entries) {
        fprintf(stderr, "table_duplicate: mem error\n");
        return -1;
    }
    hdestroy();
    int error = hcreate(1+((table->cap * 5) / 4)) == 0;
    if (error) {
        fprintf(stderr, "table_duplicate: hcreate error\n");
        return error;
    }

    ENTRY e;
    for (intptr_t i = 0; i < table->sz; ++i) {
        Entry* entry = table_get(table, i);
        if (!entry|| !entry->key) {
            fprintf(stderr, "table_duplicate: error entry not found\n");
            return -1;
        }
        char* k = strdup(entry->key);
        if (!k) {
            fprintf(stderr, "table_duplicate: mem error\n");
            return -1;
        }
        e =  (ENTRY){ .key=k, .data=(void*)i} ;
        ENTRY* ep = hsearch(e, ENTER);
        if (!ep) {
            fprintf(stderr, "table_duplicate: hsearch error\n");
            return -1;
        }
    }
    return 0;
}

int table_add_symbol(VecEntry* table, char* word) {
    intptr_t count = -1;
    char* w1 = strdup(word);
    if (!w1) {
        fprintf(stderr, "table_add_symbol: mem error\n");
        return -1;
    }
    ENTRY e = { .key = w1, .data = (void*)count };
    ENTRY* ep = hsearch(e, ENTER);
    if (!ep) {
        // unexpected, table size should be grater than htable size + 1
        fprintf(stderr, "table is full and could not be duplicated.\n");
        return -1;
    }
    intptr_t index = (intptr_t)ep->data;
    if (index < 0) {
        // new entry
        if (table->sz >= table->cap) {
            int error = table_duplicate(table);
            if (error) {
                fprintf(stderr, "table_add_symbol: error duplicating\n");
                return error;
            }

            char* w2 = strdup(word);
            if (!w2) {
                fprintf(stderr, "table_add_symbol: mem error\n");
                return -1;
            }
            e.key = w2;
            ep = hsearch(e, ENTER);
            if (!ep) {
                // unexpected, table size should be grater than htable size + 1
                fprintf(stderr, "table is full and could not be duplicated.\n");
                return -1;
            }
        }
        index = table->sz++;

        if (!ep) {
                fprintf(stderr, "WTH??\n");
                exit(1);
        }
        ep->data = (void*)index;
        char* w3 = strdup(word);
        if (!w3) {
            fprintf(stderr, "table_add_symbol: mem error\n");
            return -1;
        }
        table->entries[index] = (Entry){ .key = w3, .count = 1 };
    } else {
        ++table->entries[index].count;
        free(w1);
    }
    return 0;
}

int count_words (VecEntry* symbols, char* filename) {
     FILE *fp;
     if ((fp = fopen(filename, "r"))) {
         unsigned long nlines = 0;
         char* line = NULL;
         size_t len = 0;
         ssize_t read;
         const char* delimiters = " \t\n";

         while ((read = getline(&line, &len, fp)) != -1) {
             char* token = strtok(line, delimiters);
             while(token) {
                 int error = table_add_symbol(symbols, token);
                 if (error) {
                     return error;
                 }
                 token = strtok(NULL, delimiters);
             }
              nlines++;
         }
         fclose(fp);
     }
     return fp == NULL;
}


int main (int argc, char ** argv) {
     if (argc < 2) 
          printf("Uso: %s FILE [FILE ...]\n", argv[0]);


     // void* tree = NULL;

     const int initial_capacity = 30;
     VecEntry symbols;
     table_init(&symbols, initial_capacity);

     for (int i = 1; i < argc; i++) {
          char* fname = argv[i];
          int error = count_words(&symbols, fname);
          if (error) {
              fprintf(stderr, "error counting words in %s\n", fname);
              return -1;
          }
     }

     hdestroy();
     //qsort(symbols.entries, symbols.sz, sizeof(Entry), cmp_by_freq);

     for (int i = 0; i < symbols.sz; ++i) {
         Entry* e = table_get(&symbols, i);
         if (e) {
             printf("%s: %d\n", e->key, e->count);
             free(e->key);
         }
     }

     return 0;
}

