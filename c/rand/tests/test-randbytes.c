#include <stdio.h>

unsigned char * random_bytes (unsigned n_bytes);
unsigned long * bytes_frecuencias_en_rango (unsigned min, unsigned max,
                                       char * data, long unsigned data_size);

long unsigned cantidad = 0xFFFFFF;
unsigned data_min = 0;
unsigned data_max = 1;

int main (int argc, char ** argv) {
    char * randbytes = random_bytes(cantidad);
    unsigned long * tabla = bytes_frecuencias_en_rango (data_min, data_max,
                                                   randbytes, cantidad);
    unsigned i;
    puts("number\tfreq");
    for (i = 0; i < data_max - data_min + 1; i++)
        printf("0x%02x\t%ld\n", i + data_min, tabla[i]);
    puts("");
    return 0;
}
