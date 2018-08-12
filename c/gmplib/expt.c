/* Compile with */
/* gcc -o add_example add_example.c -lgmp -lm */

#include <stdio.h>		   
#include <stdlib.h>
#include <gmp.h>
 
int main(int argc, char *argv[])
{
  mpz_t a, res;
  unsigned long long b;
  if ( argc != 3) {
    puts("Please supply two numbers.");
    return 1;
  }
  
  mpz_init_set_str (a, argv[1], 10);
  b = atoll (argv[2]);
  mpz_init (res);

  mpz_pow_ui (res, a, b);

  printf ("%s\n", mpz_get_str (NULL, 10, res));
  
  return 0;
}
