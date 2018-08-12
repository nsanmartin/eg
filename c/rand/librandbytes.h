#ifndef _LIB_RAND_BYTES
#define _LIB_RAND_BYTES

unsigned char * random_bytes (unsigned n_bytes);
unsigned * bytes_frecuencias_en_rango (unsigned min, unsigned max,
                                       char * data, long unsigned data_size);

#endif
