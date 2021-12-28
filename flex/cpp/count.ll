%{
#include <iostream>
		
int num_lines = 0, num_chars = 0;
%}

%option noyywrap c++

%%
\n	++num_lines; ++num_chars;
.	++num_chars;
%%


// This include is required if main() is an another source file.
//#include <FlexLexer.h>

int main()
{
	yyFlexLexer lexer;
	lexer.yylex();

	std::cout << "# of lines: " << num_lines
		<< ", # of chars: " << num_chars
		<< "\n";
}
