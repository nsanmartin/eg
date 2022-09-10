#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "eg-str.h"
#include "lambda.h"

bool strEq(Str x, Str y) { return x.len == y.len && strcmp(x.cstr, y.cstr) == 0; }

void strCopy(Str s, Result* res) {
     char* mem = malloc(s.len);
     if (mem == NULL) {
         fprintf(stderr, "Memory error!\n");
         res->err = true;
     } else {
         strcpy(mem, s.cstr);
         Str rv = { .cstr = mem, .len = s.len};
         SET_POINTED_VALUE(res->ok, rv);
         res->err = false;
     }
}

