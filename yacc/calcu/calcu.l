%{
#include "calcu.tab.h"
#include <math.h>
%}

%%
([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {
    yylval.value = atof(yytext); return NUMBER; 
}

[ \t] ;

[a-z] { yylval.var_index = yytext[0] - 'a'; return NAME; }

"$"   { return 0 ; }

"\n"  |
.     return yytext[0];
%%

