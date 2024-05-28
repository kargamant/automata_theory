#include "Map.h"


/*Cell::Cell(CellType type, Cell* tBorder, Cell* bBorder, Cell* rtBorder, Cell* rbBorder, Cell* ltBorder,Cell* lbBorder) : type(type), tBorder(tBorder), bBorder(bBorder), rtBorder(rtBorder), rbBorder(rbBorder), ltBorder(ltBorder), lbBorder(lbBorder)
{
	
}*/
std::string nameByType(CellType type)
{
	switch(type)
	{
		case CellType::obstacle:
			return "O";
		case CellType::ground:
			return "G";
		default:
			return "";
	}
}

Map::Map(int m, int n) : m(m), n(n)
{
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			map.insert({{i, j}, {CellType::ground, i, j}});
		}
	}
}

void operator<<(std::ostream& stream, Cell& cell)
{
	stream<<"<"<<nameByType(cell.type)<<">";
}

void operator<<(std::ostream& stream, Map& map)
{
	for(int i=0; i<map.m; i++)
	{
		for(int j=0; j<map.n; j++)
		{
			if(map.robo.getX()==i && map.robo.getY()==j) stream<<map.robo;
			else stream<<map.map[{i, j}];
			stream<<" ";
		}
		stream<<std::endl;
	}
}

void Map::changeCellType(int x, int y, CellType ntype)
{
	changeCellType({x, y}, ntype);
}

void Map::changeCellType(std::pair<int, int> xy, CellType ntype)
{
	map[xy].type=ntype;
}

void Map::setRobo(Robo& robo)
{
	this->robo=robo;
}
















