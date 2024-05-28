all:
	./fb_compile.sh
	g++ -g -std=c++20 bison/bis.tab.c flex/lex.yy.c test.cpp VarMap/VarMap.cpp Ast/Ast.cpp Robo/Map.cpp Robo/Robo.cpp -o test
