#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#include <unistd.h>
#include <sys/stat.h>
/* #include <ctype.h> */
#define MAX_LINE_SIZE 1024

unsigned estimated_line_size (FILE * fp, const unsigned sample_lines_to_read);

void read_hash_table_from_file(FILE * stream, const unsigned ndefs);
int es_en_palabra (const char c);
void print_stdin_trad ();
void print_help();

void check_dictionary (char * filename, struct stat * statptr);
void check_file (char * filename, FILE *fp);

/*
 * Uso: cat text | ./prog -d diccionario
 *
 */


int main (int argc, char ** argv) {

  char opt; // para getopts
  char * diccionario_filename = 0x0;
  while ((opt = getopt (argc, argv, "d:f:h")) != -1)
    switch (opt)
      {
      case 'd':
	diccionario_filename = optarg;
	break;
      case 'f':
	puts("Por ahora solo stdin.");
	exit(1);
      case 'h':
	print_help();
	exit(1);
      }
    

  struct stat dicc_st;   /* Me fijo si el diccionario existe */
  check_dictionary (diccionario_filename, &dicc_st);


  FILE *fp = fopen (diccionario_filename, "r");
  check_file (diccionario_filename, fp);

    
  unsigned ndefs = dicc_st . st_size / estimated_line_size(fp, 5);
  fseek (fp, 0, SEEK_SET);

  /* Escribo en el diccionario.*/
  read_hash_table_from_file(fp, ndefs + (ndefs << 2) / 3);
  fclose (fp);
  print_stdin_trad();
    
  return 0;
}



unsigned estimated_line_size (FILE * fp, const unsigned sample_lines_to_read)
{

  /* Leo las primeras lineas y me fijo cuantocupan en promedio*/
  char * line = 0x0;
  unsigned lines_read, acum;
  lines_read = acum = 0;
  size_t len = 0;
  ssize_t line_size;
    
  while ( (line_size = getline(&line, &len, fp)) != -1 
	  && lines_read ++ < sample_lines_to_read ) {
    acum += line_size;
  }

  return acum / lines_read;
    
}

void read_hash_table_from_file(FILE * fp, const unsigned ndefs )
{
  const char pattern_no_palabra[] = "\n\t:;/. ";
  const char pattern_espacio[] = "\n\t ";

  /* Creo el hash table */
  if (! hcreate ( ndefs ) ) {
    fprintf (stderr, "Error: no pudo crearse hash table.");
    exit(1);
  }

  char * palabra, * definicion, * line_check, * line_buff = 0x0;
  size_t line_size  = 0;
  unsigned n_linea = 0;
  ENTRY e /*, *e_check*/;
  
  while ( getline (&line_buff, &line_size, fp) > 0 )
    {
      if (*line_buff == '#' || *line_buff == '\n') 
	continue;
      palabra = strtok (line_buff, pattern_no_palabra);
      if (!palabra)
	continue;
      definicion = strtok (0x0, pattern_espacio);
      if (!definicion) {
	fprintf (stderr,
		 "Error en linea %d.\n"
		 "Palabra sin definir.\n"
		 "linea: %s\n"
		 "palabra: %s",
		 n_linea, line_buff, palabra); exit(1);
      }
        
      line_check = strtok (0x0, ":;/ ");
      /* <key, value> pair */
      e . key = strdup (palabra);
      e . data = strdup (definicion);
        
      if (line_check && *line_check != '\n') {
	fprintf (stderr,
		 "Error en linea %d.\n"
		 "linea: %s",
		 n_linea, line_buff); exit(1);
      }
      /* defino */
      hsearch (e, ENTER);
    }
}

void print_stdin_trad ()
{
    unsigned buff_size = 1024;
    char * buff = (char*)malloc (buff_size);
    int i, c = 1;
    i = 0;
    ENTRY e, *ep;
    /*
     * Leo caracter por caracter y cada vez que obtengo una palabra
     * me fijo en el diccionario. Si est�, le agrego su def.
     */

    while ((c = getc (stdin)) != -1) {
	if (i + 1 > buff_size) {
	    puts("print_stdin_trad: Buffer quedo chico. Exit."); exit(1);
	}
	
	if (!es_en_palabra(c)) {
	    if (i > 0) {
		buff [i] = '\0';
		e . key = buff;
		ep = hsearch (e, FIND);
		if (ep) 
		    printf("%s %s", buff, (char *) ep -> data);
		else 
		    printf("%s", buff);
		i = 0;
	    }
	    printf("%c", c);
	    continue;
	}
	buff[i++] = c;
    }
    free (buff);
}

int es_en_palabra (const char c)
{
  return
    (c >= '0' && c <= '9')
    || (c >= 'A' && c <= 'Z')
    || (c >= 'a' && c <= 'z');
}

void print_help() {
  puts("Uso: cat TEXTO | ./prog -d DOCCIONARIO\n");
  puts("donde TEXTO es cualquier texto y DICCIONARIO tiene");
  puts("PAL_1 espacio SDO_1");
  puts("PAL_2 espacio SDO_2\n...");
  puts("Con unsa definicion por linea.");
}

void check_dictionary (char * filename, struct stat * statptr)
{
  if (!filename) {					
    puts("Debe proveer un diccionario.");		
    exit(1);						
  }							
  else if (stat (filename, statptr) != 0) {	
    fprintf (stderr,					
	     "error: Problema con el archivo %s.\n",	
	     filename);				
    exit(1);						
  }							

}

void check_file (char * filename, FILE *fp)
{
  if (!fp) {
    fprintf (stderr,					
	     "Hubo un problema al intentar abrir %s\n", 
	     filename);				
    exit(1);						
  }
}
