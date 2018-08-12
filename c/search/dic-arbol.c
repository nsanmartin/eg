#include <search.h>
#include <stdio.h>
#include <stdlib.h>

#define LEN(ARR) sizeof(ARR)/sizeof(*(ARR))

void definir (const void *key, void ** rootp, int (*compar) (const void*, const void*) );

struct par {
    int clave;
    char significado;
};
        
int par_cmp (const void * x, const  void * y);
int par_copy (struct par * de, struct par ** a);

int main (int argc, char ** argv)
{
    void * arbol = NULL;
    struct par pares[] =
        {
            { 1, 'u' },
            { 2, 'd' },
            { 4, 'c' },
            { 6, 's' },
            { 10, 'z' },
            { 12, 'c' }
        };
    struct par * e, **e2;
    /* guardo */
    for (int i = 0; i < LEN(pares); i++) {
        par_copy (&pares[i], &e);
        printf ("guardo %4d = %c  en %p \n",
                e -> clave, e -> significado, e);
        definir (e, &arbol, par_cmp);
    }
    /* busco */
    struct par buscar_par;
    struct par ** encontrado;
    for (int i = 0; i < 20; i++) {
        buscar_par.clave = i;
        encontrado = tfind (&buscar_par, &arbol, par_cmp);
        if (encontrado) {
            printf("busco %d\t", buscar_par.clave);
            struct par * ptr;
            ptr = *encontrado;
            printf ( "clave: %d \tsdo: %c\n", ptr->clave, ptr->significado);
        }
        else
            printf("No encontre' %d\n", i);
    }
}

int par_cmp (const void * x, const  void * y)
{
    const struct par * p = x;
    const struct par * q = y;
    return p -> clave - q -> clave;
}

void definir (const void *key, void ** rootp,
              int (*compar) (const void*, const void*))
{
    // key debe ser un puntero a una nueva copia del dato.
    if (!tsearch (key, rootp, compar)) {
        puts ("no hay memoria");
        exit(1);
    }

}

int par_copy (struct par * de, struct par ** a)
{
    if (!(*a = malloc (sizeof(struct par))))
        return 1;
    (*a) -> clave = de -> clave;
    (*a) -> significado = de -> significado;
    return 0;
}

