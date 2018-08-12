#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main(int argc, char ** argv)
{
    
    long long x;

    char * tail;
    int i;
    for (i = 1; i < argc; i++) {
        errno = 0;
        x = strtoull (argv[i], &tail, 10);
        if (errno == ERANGE) { puts("demasiado grande"); }
        else if (errno) { puts("NaN");}
        else printf ("%lld\n", x);
    }
}
