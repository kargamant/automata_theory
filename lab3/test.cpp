#include "bison/bis.tab.h"
#include "Robo/Map.h"

extern FILE* yyin;

int main(int argc, char* argv[])
{
	Map map{5, 5};
	Robo robo(0, 0, 150);
	map.changeCellType(0, 1, CellType::obstacle);
	map.changeCellType(0, 2, CellType::obstacle);
	map.changeCellType(1, 2, CellType::obstacle);
	map.setRobo(robo);
	std::cout<<map;
	map.rrRobo();
	std::cout<<map;
	map.rrRobo();
	std::cout<<map;
	map.moveRobo();
	map.rrRobo();
	std::cout<<map;
	map.moveRobo();
	std::cout<<map;
	auto scan=map.getRobo().sonar();
	for(auto& pair: scan)
	{
		std::cout<<pair.first<<" "<<pair.second<<std::endl;
	}
	std::cout<<map.sonarRobo()<<std::endl;


	//if(argc==2) yyin=fopen(argv[1], "r");
	//yyparse();
	return 0;
}
