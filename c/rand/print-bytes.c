#include <stdint.h>
#include <stdio.h>

void print_table_bytes (uint64_t length, uint64_t * tabla) {
  uint64_t i;
  for (i = 0; i < length; i++) 
    printf("0x%02x\t%d\n", i , tabla[i]);
  puts("");
}

void print_table_uint64 (uint64_t length, uint64_t * tabla) {
  uint64_t i;
  for (i = 0; i < length; i++) 
    printf("0x%08x\t%d\n", i , tabla[i]);
  puts("");
}
