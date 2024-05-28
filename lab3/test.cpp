#include "bison/bis.tab.h"
#include "Robo/Map.h"

extern FILE* yyin;

int main(int argc, char* argv[])
{
	Map map{5, 5};
	map.changeCellType(0, 0, CellType::obstacle);
	map.changeCellType(0, 1, CellType::obstacle);
	map.changeCellType(0, 2, CellType::obstacle);
	std::cout<<map;
	//if(argc==2) yyin=fopen(argv[1], "r");
	//yyparse();
	return 0;
}
