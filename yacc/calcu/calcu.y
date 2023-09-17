%{
#include <stdio.h>
int yylex (void);
void yyerror(char const*);
double vars[26] = {0};
%}

%union {
    double value;
    unsigned var_index;
}

%token <var_index> NAME
%token <value>     NUMBER
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS

%type <value> expr

%%
statement_list: statement '\n'
              | statement_list statement '\n'
              ;
statement: NAME '=' expr { vars[$1] = $3; }
         | expr { printf("= %g\n", $1); }
         ;

expr: expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr {
        if ($3 == 0) { yyerror("div by zero"); return -1; }
        else { $$ = $1 / $3; }
    }
    | '-' expr     { $$ = -$2; }
    | '(' expr ')' { $$ = $2; }
    | NUMBER       { $$ = $1; } 
    | NAME         { $$ = vars[$1]; }
    ;

%%

extern FILE* yyin;

int main() {
    yyparse();
}

void yyerror(char const* s) {
    fprintf(stderr, "error: %s\n", s);
}
