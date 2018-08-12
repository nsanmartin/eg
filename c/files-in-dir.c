#define _GNU_SOURCE /* for get_current_dir_name */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <unistd.h>
#include <string.h>

     
struct arr {
    char ** nombres;
    int capacidad;
    int longitud;
};

struct arr * arr_nuevo () {
    struct arr * res = malloc(sizeof(struct arr));
    res -> nombres = malloc(sizeof(char*)*2);
    res -> capacidad = 2;
    res -> longitud = 0;
    return res;
}

void agregar(struct arr * a, char * nombre) {
    if (a -> longitud == a -> capacidad) {
        a -> nombres = realloc (a -> nombres, sizeof(char*) * a -> capacidad * 2);
        a -> capacidad *= 2;
    } 
    a -> nombres [a -> longitud] = strdup(nombre);
    a -> longitud++;
}

static int
cmpstringp (const void * s, const void * t) {
    return strcmp (* (char * const *) s, * (char * const *) t);
}


struct arr * dir_files(char * dirpath) {
    struct arr * narr = arr_nuevo();
    DIR *d;
    if ( d = opendir (dirpath)) {
        struct dirent *dentry;
        while ((dentry = readdir(d)) != NULL) {
             agregar(narr, dentry -> d_name);
        }
        closedir(d);
    } else {
        fprintf(stderr, "error: no pude abrir %s\n", dirpath);
        return NULL;
    }

    return narr;
}

int esta_bin(char * fname, struct arr * farr) {
     /* binary search */
     int desde = 0;
     int hasta = farr -> longitud;
     int med;
     char ** nombres = farr -> nombres;
     int cmp;
     while (desde < hasta - 1) {
          med = (desde + hasta) / 2;
          cmp = strcmp(fname, nombres[med]);
          if (cmp < 0)
               hasta = med;
          else if (cmp > 0)
               desde = med;
          else if (cmp == 0)
               break;
     }
     return cmp == 0 ? 1 : 0;
}
int main (int argc, char ** argv) {
     if (argc < 3)
          puts("is in dir:")
          printf("uso: %s FILE [FILE ...] DIR\n", argv[0]);
     else {
          int si, no;
          si = no = 0;
          struct arr * files = dir_files (argv[argc - 1 ]);
          qsort (files -> nombres, files -> longitud, sizeof(char*), cmpstringp);
          for (int i = 1; i < argc - 1; i++) {
               int test = esta_bin (argv[i], files);
               si += test;
               no += 1 - test;
               printf("%s esta %s\n", test ? "si": "no", argv[i]);
          }
          printf("si: %d\tno: %d\n", si, no);
     }
     return 0;
}
