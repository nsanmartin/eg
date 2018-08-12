#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{

   char c;
   
   while ((c = getopt (argc, argv, "abc:d:")) != -1)
   {
      switch (c)
      {
	 case 'a':
	    printf("caso \'a\'\n");
	    return 0;
	 case 'b':
	    printf("caso \'b\'\n");
	    break;
	 case 'c':
	    printf("caso \'c\'\n");
	    printf("argumento dado a la opci'on: %s\n", optarg);
	    break;
	 case 'd':
	    printf("caso \'d\'\n");
	    printf("argumento dado a la opci'on: %s\n", optarg);
	    return 0;
	 case '?':
	    if (isprint (optopt))
	    {
	       fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
	    }
	    else
	       fprintf (stderr,
			"Caracter de opcion desconocido `\\x%x'.\n",
			optopt);
	    return 1;
	 default:
	    abort ();
	
      }
   }
   printf("salgo de getopts\n");
   return 0;
}

