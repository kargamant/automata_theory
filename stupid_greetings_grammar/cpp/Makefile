all:
	bison -d -L C++ hype.yy
	flex -+ recognizer_hype.ll
	g++ hype.tab.cc lex.yy.cc main.cpp Interpreter.cpp -o prog
