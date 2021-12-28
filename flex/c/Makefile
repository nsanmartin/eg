LEX_GENERATED=lex.yy.c

%:
	flex $@.l && gcc -lm -lfl $(LEX_GENERATED)

clean:
	rm $(LEX_GENERATED) a.out
