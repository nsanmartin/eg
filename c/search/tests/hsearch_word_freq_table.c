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
    *v = (VecEntry){
        .sz = 0,
        .cap = initial_capacity,
        .entries = malloc(initial_capacity * sizeof(Entry))
    };
    if (!v->entries) { return -1; }
    int initial_htable_size = 1 + ((v->cap * 5) / 4);
    int error = hcreate(initial_htable_size) == 0;
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
        return -1;
    }
    hdestroy();
    int error = hcreate(1+((table->cap * 5) / 4)) == 0;
    if (error)
        return error;

    ENTRY e;
    for (intptr_t i = 0; i < table->sz; ++i) {
        e =  (ENTRY){ .key=table_get(table, i)->key, .data=(void*)i} ;
        hsearch(e, ENTER);
    }
    return 0;
}

int table_add_symbol(VecEntry* table, char* word) {
    intptr_t count = -1;
    ENTRY e = { .key = word, .data = (void*)count };
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
            if (error) 
                return error;

            ep = hsearch(e, ENTER);
            if (!ep) {
                // unexpected, table size should be grater than htable size + 1
                fprintf(stderr, "table is full and could not be duplicated.\n");
                return -1;
            }
        }
        index = table->sz++;
        //ep = hsearch(e, ENTER);
        //if (!ep) {
        //    // unexpected, table size should be grater than htable size + 1
        //    fprintf(stderr, "table is full but was just duplicated :/!\n");
        //    return -1;
        //}

        if (!ep) {
                fprintf(stderr, "WTH??\n");
                exit(1);
        }
        ep->data = (void*)index;
        ep->key = strdup(word);
        table->entries[index] = (Entry){ .key = ep->key, .count = 1 };
        //table->entries[index] = (Entry){ .key = strdup(word), .count = 1 };
    } else {
        ++table->entries[index].count;
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
                 //printf("`%s'\n", token);
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

     //qsort(symbols.entries, symbols.sz, sizeof(Entry), cmp_by_freq);

     for (int i = 0; i < symbols.sz; ++i) {
         Entry* e = table_get(&symbols, i);
         if (e) {
             printf("%s: %d\n", e->key, e->count);
         }
     }

     return 0;
}

