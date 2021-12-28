LEX_GENERATED=lex.yy.c

%:
	flex $@.l && gcc -lm -lfl $(LEX_GENERATED)

count:
	flex $@.l && gcc -lm -lfl $(LEX_GENERATED)

username:
	flex $@.l && gcc -lm -lfl $(LEX_GENERATED)

clean:
	rm $(LEX_GENERATED) a.out
