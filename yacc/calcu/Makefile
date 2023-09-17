calcu: calcu.l calcu.y
	bison -d calcu.y
	flex calcu.l
	gcc -o calcu calcu.tab.c lex.yy.c -ll


clean:
	rm calcu calcu.tab.*
