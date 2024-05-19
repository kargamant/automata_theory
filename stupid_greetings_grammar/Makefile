all:
	bison -v -d lang.yy -o bis.tab.c
	flex lang.ll
	gcc bis.tab.c lex.yy.c main.c -o prog
