#ifndef __CALCU_H__
#define  __CALCU_H__

#include <stdio.h>

#define NVARS 26

int yylex (void);
void yyerror(char const*);
int readParams(int argc, char* argv[]);
extern double vars[NVARS];
#endif
