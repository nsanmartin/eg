#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char * dni;
unsigned int cod[10] = { 5, 4, 3, 2, 7, 6, 5, 4, 3, 2 };
void print_dni();
unsigned calcular_verif ();
    
int main (int argc, char ** argv)
{
    if (argc != 2) return 0;
    dni = argv [1];
    if (strlen (dni) != 10 ) {
        fprintf (stderr, "mal ingresado el dni\n");
        exit(1);
    }
    print_dni();
    unsigned verif = calcular_verif ();
    printf ("codigo verif: %d", verif);
}

void print_dni () {
    int i = 0;
    printf ("dni: ");
    while ( i < 10 ) {
        printf("%c", dni[i]);
        i++;
    }
    printf ("\n");

}

unsigned calcular_verif () {
    int v1, v2, v3, i;
    v1 = i = 0;
    while ( i < 10 ) {
        v1 += (dni[i] - '0')  * cod[i];
        i++;
    }
    v2 = v1 % 11;
    v3 = 11 - v2;
    if ( v3 == 11) {
        v3 = 0;
    } else if ( v3 == 10 ) {
        v3 = 9;
    }
    return v3;
}
