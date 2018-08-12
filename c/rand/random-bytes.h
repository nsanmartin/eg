#ifndef __RAND_BYTES_H_
#define __RAND_BYTES_H_
#include <stdint.h>


unsigned char * random_bytes (uint64_t n_bytes);
uint64_t * bytes_frecuencias_en_rango (uint64_t modulo,
                                       char * data, uint64_t data_size);
uint64_t * int64_frecuencias_en_rango (uint64_t modulo,
                                       uint64_t * data, uint64_t data_size);

unsigned long random_long ();
unsigned long rand_in_range_urandom (unsigned long range);
uint64_t * rand_ints_in_range_urandom (uint64_t range, uint64_t count) ;

#define MAX_ALLOWED(range) \
  (0xFFFFFFFF -  (((0xFFFFFFFF % (range)) + 1 ) % (range)))


#endif // __RAND_BYTES_H_
