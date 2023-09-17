%{

	int nlines = 0, nwords = 0, nchars = 0;

%}

%%

[^ \t\n]+ 	{ ++nwords; nchars += yyleng; }
\n	{ ++nlines; ++nchars; }
.	++nchars;

%%

int main() {
	yylex();
	printf("\t%d\t%d\t%d\n", nlines, nwords, nchars);
}
