/* Compile with */
/* gcc -o add_example add_example.c -lgmp -lm */

#include <stdio.h>
#include <gmp.h>
 
int main(int argc, char *argv[])
{
  mpz_t a, b;
  if (argc < 3) {
    puts("Please supply two numbers to add.");
    return 1;
  }
  /* Assume decimal integers */
  mpz_init_set_str (a, argv[1], 10);	
  mpz_init_set_str (b, argv[2], 10);
  mpz_add (a, a, b);			/* a=a+b */

  printf ("%s\n", mpz_get_str (NULL, 10, a));
  return 0;
}
