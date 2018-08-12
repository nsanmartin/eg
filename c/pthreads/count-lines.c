#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void* count_lines (void* args) ;
//struct cw_args* new_cw_args(char const* filename);

struct cw_args {
     char const * filename;
     unsigned long nlines;
};

int main (int argc, char ** argv) {
     if (argc < 2) {
          printf("Uso: %s FILE [FILE ...]\n", argv[0]);
          return 0;
     }
     pthread_t *thread = malloc (sizeof(pthread_t) * argc - 1);
     struct cw_args * args = malloc (sizeof(struct cw_args) * argc - 1);
     
     for (int i = 1; i < argc; i++) {
          args[i].filename = strdup(argv[i]);
          args[i].nlines = 0;
          pthread_create(&thread[i], NULL, count_lines, (void*) &args[i]);
     }

     unsigned long total = 0;
     for (int i = 1; i < argc; i++) {
          pthread_join (thread[i], NULL);
          total += args[i].nlines;
          printf ("%s tiene %lu lineas\n", argv[i], args[i].nlines);
     }

     printf("total: %lu lineas.\n", total);
     free (thread); free(args);
     return 0;
}

void *count_lines (void* cw_args) {
     struct cw_args* args = (struct cw_args*)cw_args;
     FILE *fp;
     if ((fp = fopen(args -> filename, "r")) == 0) {
          printf("error leyendo %s.\n", args -> filename);
          exit(1);
     }
     char *line = NULL;
     size_t len = 0;
     ssize_t read;
     while ((read = getline(&line, &len, fp)) != -1) {
          args -> nlines++;
     }
     fclose(fp);
     return NULL;
}
