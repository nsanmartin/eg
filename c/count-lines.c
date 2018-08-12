#include <stdio.h>
#include <stdlib.h>

unsigned long count_lines (char* filename) ;


int main (int argc, char ** argv) {
     if (argc < 2) 
          printf("Uso: %s FILE [FILE ...]\n", argv[0]);

     unsigned long total = 0; 
     for (int i = 1; i < argc; i++) {
          unsigned long nlines = count_lines(argv[i]);
          total += nlines;
          printf ("%s tiene %lu lineas\n", argv[i], nlines);
     }
     printf("total: %lu lineas.\n", total);
     return 0;
}


unsigned long count_lines (char* filename) {

     FILE *fp;
     if ((fp = fopen(filename, "r")) == 0) {
          printf("error leyenfo %s.\n", filename);
          exit(1);
     }
     unsigned long nlines = 0;
     char *line = NULL;
     size_t len = 0;
     ssize_t read;

     while ((read = getline(&line, &len, fp)) != -1) {
          nlines++;
     }
     fclose(fp);
     return nlines;
}
