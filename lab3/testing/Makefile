all:
	cd .. && ./fb_compile.sh
	g++ -g -std=c++20 testing.cpp ../bison/bis.tab.c ../flex/lex.yy.c ../VarMap/VarMap.cpp ../Ast/Ast.cpp ../Robo/Map.cpp ../Robo/Robo.cpp -o unit_tests
