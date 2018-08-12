/*
  Ejemplo de mal (peligroso) uso de strcpy.
  Como no controlo cuantos bytes escribo en 
  buffer, termino escribiendo en filename.

  compilar con -fni-stack-protection
  y ejecutar:
  $ ./a.out "0123456 CAMBIO FILENAME"

*/

#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 8

int main (int argc, char** argv) {

     char filename[] = "~/tmp.f";   /* este buffer se sobrescribe con strcpy */
     char buffer[BUFF_SIZE];        /* este tambien, obvio */
     char other_buffer[] = "text";  /* este ya no */
     
     printf ("filename: %s\n", filename);
     printf ("other_buffer: %s\n", other_buffer); 
     strcpy (buffer, argv[1]);
     puts("strcpy...");
     printf("buffer: '%s'\n", buffer);
     printf("filename: '%s'\n", filename);
     printf ("other_buffer: %s\n", other_buffer); 
          
     return 0;
}
