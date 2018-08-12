#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
/*
 * hsearch sólo funciona con 'zero-terminated strings'
 */
void crear_diccionario (unsigned ndefs);
void definir (char * clave, char * significado);
int obtener (char * const clave, char ** significado);


int main (int argc, char ** argv) {
  return 0;
}

void crear_diccionario (unsigned ndefs) {
  if (! hcreate ( ndefs ) ) {
    fprintf (stderr, "Error: no pudo crearse hash table."); exit(1);
  }
}

void definir (char * const clave, char * const significado) {
  ENTRY e;
  e . key = strdup (clave);
  e . data = strdup (significado);
  hsearch (e, ENTER);
}

int obtener (char * const clave, char ** significado) {
    ENTRY e, *ep;
    e . key = clave;
    if(ep = hsearch (e, FIND)) {
      *significado = ep -> data;
      return 1;
    } else { return 0; }
}
