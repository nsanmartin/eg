#include "calcu.h"

extern FILE* yyin;
double vars[NVARS] = {0};

void yyerror(char const* s) {
    fprintf(stderr, "error: %s\n", s);
}

int readParams(int argc, char* argv[]) {
    if (argc > 1) {
        FILE* f = fopen(argv[1], "r");
        if (f) {
            yyin = f;
        } else {
            fprintf(stderr, "error opening file: %s\n", argv[1]);
            return -1;
        }
    }
    return 0;
}
