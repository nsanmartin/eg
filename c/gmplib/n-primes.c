/* Compile with */
/* gcc -o nprimos n-primos.c -lgmp -lm */

#include <gmp.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
//void veces_que_divide(mpz_t veces, const mpz_t d,  mpz_t n);

struct primos {
    mpz_t num;
    struct primos * next;
};

int es_divisible_por_alguno (mpz_t n, struct primos * pms);
struct primos * agregar_al_final (struct primos * pms, mpz_t n);
void primos_init_ui (struct primos ** pms, unsigned long long ui);

//void print_primos (Primos p);

int main(int argc, char *argv[])
{
    if ( argc != 2 ) { puts("Uso: n-primos NUMERO"); return 1; }

    unsigned long long  x;
    errno = 0;
    char * tail;
    x = strtoul (argv[1], &tail, 10);
    if (errno) { puts("segundo numero demasiado grande"); return 0; }

    mpz_t n, i;
    mpz_init_set_str (n, argv[1], 10);
    if ( x == 0) { return 0 ;}

    struct primos * pms, * qms, * ult;
    primos_init_ui (&pms, 2);
    ult = pms;
    printf ("2");
    mpz_init_set_ui(i, 3);
    unsigned long long j = 1;
    while (j < x)//mpz_cmp_ui(n, 1))// && i < 1)
    {
	if (!es_divisible_por_alguno (i, pms)) {
	    ult = agregar_al_final (ult, i);
	    gmp_printf (" %Zd", i);
            j++;

	}	
	mpz_add_ui (i, i, 2);
    }

    puts("");
    mpz_clear(n);
    mpz_clear(i);
    return 0;
}

/* void veces_que_divide(mpz_t veces, const mpz_t d, mpz_t n) */
/* { */
/*     if (!mpz_cmp_ui(d, 1)) */
/*     { */
/*         mpz_set (veces, n); */
/*         mpz_set_ui (n, 1); */
/*         return; */
/*     } */

/*     mpz_set_ui(veces, 0); */

/*     while (mpz_divisible_p(n, d)) */
/*     { */
/*         mpz_add_ui (veces, veces, 1); */
/*         mpz_divexact (n, n, d); */
/*     } */
/* } */

int es_divisible_por_alguno (mpz_t n, struct primos * primos)
{
    int ret = 0;
    struct primos * p = primos;
    mpz_t cuad;
    mpz_init_set_ui (cuad, 4);
    while (p && mpz_cmp (cuad, n) <= 0)
    {
        if (mpz_divisible_p (n, p -> num)) {
            ret = 1;
            break;
        }
        p = p -> next;
        mpz_mul (cuad, p -> num, p -> num);
    }
    mpz_clear(cuad);
    return ret;
}

struct primos * agregar_al_final (struct primos * pms, mpz_t n)
{
    while (pms -> next) { pms = pms -> next; }
    struct primos * nuevo = malloc (sizeof (struct primos));
    if (!nuevo) { puts("No mas memotia");exit (1); }
    mpz_init_set (nuevo -> num, n);
    nuevo -> next = 0x0;
    pms -> next = nuevo;
    return nuevo;
}

/* void print_primos (Primos primos) */
/* { */
/*     Primos p = primos; */
/*     while (p != 0x0) */
/*     { */
/* 	gmp_printf ("%Zd ", p -> num); */
/* 	p = p -> next; */
/*     } */
/* } */

void primos_init_ui (struct primos ** pms, unsigned long long ui)
{
    struct primos * nuevo;
    nuevo = (struct primos *) malloc (sizeof (struct primos));
    mpz_t n;
    mpz_init_set_ui (nuevo -> num, ui);
    nuevo -> next = 0x0;
    *pms = nuevo;
}
