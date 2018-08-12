#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned char * random_bytes (unsigned n_bytes) {
    FILE * urand = fopen("/dev/urandom", "r");
    unsigned char byte;
    unsigned char * random_bytes = malloc (sizeof (char) * n_bytes);
    if (n_bytes != fread (random_bytes, 1, n_bytes, urand)) {
        fprintf(stderr, "Error leyendo /dev/urandom"); exit(1);
    }
    fclose(urand);
    return random_bytes;
}

unsigned long * bytes_frecuencias_en_rango (
    unsigned min, unsigned max,
    char * data, unsigned long data_size) {
    unsigned long * tabla = malloc (sizeof(unsigned long) * (max - min + 1));
    int i;
    for (i = min; i < max - min + 1; i++) { tabla[i] = 0; }
    for (i = 0; i < data_size; i++) {
        tabla[data[i] % (max - min + 1)] ++;
    }
    return tabla;
}
        
