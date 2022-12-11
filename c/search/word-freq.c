#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string-hash-table.h>

#define INITSZ 40

int cmp_by_freq(const void* p, const void* q) 
{
    const Entry* x = p;
    const Entry* y = q;
    const intptr_t xcount = (intptr_t) x->value;
    const intptr_t ycount = (intptr_t) y->value;
    return xcount - ycount;
}

int table_add_symbol(HashTable* t, char* word) 
{
    Entry* e = hashTableSearch(t, word);
    if (!e) 
        return -1;
    e->value = (void*) 1+(intptr_t)e->value;
    return 0;
}

int count_words (HashTable* symbols, char* filename) 
{
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


    HashTable symbols;
    hashTableInit(&symbols, INITSZ);

     for (int i = 1; i < argc; i++) {
          char* fname = argv[i];
          int error = count_words(&symbols, fname);
          if (error) {
              fprintf(stderr, "error counting words in %s\n", fname);
              return -1;
          }
     }

     // qsort(symbols.table, symbols.size, sizeof(Entry), cmp_by_freq);

     for (int i = 0; i < symbols.size; ++i) {
         Entry e = symbols.table[i];
         intptr_t count = (intptr_t)e.value;

         if (count) {
             printf("%s: %ld\n", e.key, count);
         }
     }

     return 0;
}

