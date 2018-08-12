#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

mpz_t * read_nums (unsigned n, char ** v);
void print_nums(unsigned n, mpz_t * nums);

int main (int argc, char ** argv) {
    unsigned n = argc -1;
    mpz_t * nums = read_nums (n, argv + 1);
    print_nums(n, nums);
}


mpz_t * read_nums (unsigned n, char ** v) {
    unsigned i;
    mpz_t * numeros = malloc (sizeof(mpz_t)*n);
    for (i = 0; i < n; i++) {
        mpz_init_set_str (numeros[i], v[i], 10);
    }
    return numeros;
}

void print_nums(unsigned n, mpz_t * nums) {
    unsigned i;
    for (i = 0; i < n; i++) {
        gmp_printf ("%d: %Zd\n", i, nums[i]);
    }
}
    
