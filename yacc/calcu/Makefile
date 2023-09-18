calcu: calcu.l calcu.y
	bison -d calcu.y
	flex calcu.l
	gcc -o calcu calcu.c calcu.tab.c lex.yy.c -ll 


clean:
	rm calcu calcu.tab.*
