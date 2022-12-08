#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#define _GNU_SOURCE

typedef struct {
    int count;
    char* key;
} Entry;

int entry_cmp(const void* p, const void* q) { return strcmp(((Entry*)p)->key, ((Entry*)q)->key); }

void free_node(void* nodep) {
    printf("free node\n");
    Entry* e = nodep;
    free(e->key);
    free(e);
}

void tree_visitor(const void* node, VISIT which, int depth) {
    if (which == postorder || which == leaf) {
        const Entry* entry = *(Entry**)node;
        printf("%s: %d\n", entry->key, entry->count);
    }
}


int add_word(void** tree, char* word) {
    if (!word) { return 1; }
    Entry* p = malloc(sizeof(Entry));
    if (!p) {
        return 1;
    }
    *p = (Entry) { .key = word, .count = 0 };
    Entry** node = tsearch(p, tree, entry_cmp);
    if (!node) {
        free(p);
        return 1;
    }
    Entry* q = *node;

    if (q != p) {
        free(p);
    } else {
        p->key = strdup(word);
    }
    ++q->count;
    return 0;
}

int count_words (void** tree, char* filename) {

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
                 int error = add_word(tree, token);
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


     void* tree = NULL;

     for (int i = 1; i < argc; i++) {
          char* fname = argv[i];
          int error = count_words(&tree, fname);
          if (error) {
              fprintf(stderr, "error reading %s\n", fname);
          }
     }

     twalk(tree, tree_visitor);
     tdestroy(tree, free_node);
     return 0;
}


