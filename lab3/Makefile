all:
	bison -v -d lang.y -o bis.tab.c
	flex recognizer.l
	gcc bis.tab.c lex.yy.c test.c -o test
