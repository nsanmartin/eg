#include <stddef.h>
#include <stdio.h>

#include "lambda.h"


void incr(Lambda* lam, void* x) {
    int* value = lam->value;
    char c = GET_POINTED_VALUE(char, x);
    c++;
    //LAMBDA_SET_VALUE(lam, c);
    char* lv = lam->value;
    *lv = c;
}

void transform(Lambda* lambda, char* in) {
    while (*in) {
        lambda->app(lambda, in);
        char rv = GET_POINTED_VALUE(char, lambda->value);
        //char rv = *(char*) lambda.value;
        *in = rv;
        ++in;
    }
}


int main () {
    char lam_rv;
    Lambda lam = { .app = &incr, .value = &lam_rv, .ctx = NULL };
    char hw[] = "hello world";
    printf("%s", hw);
    puts("");
    transform(&lam, hw);
    printf("%s", hw);
    puts("");
}
