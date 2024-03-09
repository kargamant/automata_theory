all:
	flex -+ rules.l
	g++ -o main lex.yy.cc FlexRecognizer.cpp -lfl
no_out:
	flex rules_no_out.l
	gcc -o main lex.yy.c -lfl
