#include "Map.h"
#include <vector>
#include <fstream>


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
		case CellType::escape:
			return "E";
		default:
			return "";
	}
}

Map::Map(int m, int n) : m(m), n(n), robo(0, 0, 30)
{
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			map.insert({{i, j}, {CellType::ground, i, j}});
		}
	}
}

Map::Map(const std::string& filename)
{
	std::ifstream fs{filename};
	std::string line;
	std::getline(fs, line);
	m=std::stoi(line.substr(0, line.find(" ")));
	n=std::stoi(line.substr(line.find(" "), line.length()));
	line.clear();
	for(int i=0; i<m; i++)
	{
		std::getline(fs, line);
		for(int j=0; j<n; j++)
		{
			if(line[j]=='0')
			{
				map.insert({{i, j}, {CellType::ground, i, j}});
			}
			else if(line[j]=='1')
			{
				map.insert({{i, j}, {CellType::obstacle, i, j}});
			}
			else if(line[j]=='2')
			{
				map.insert({{i, j}, {CellType::escape, i, j}});
			}
			else if(line[j]=='r')
			{
				robo.setCoordinates({i, j});	
				robo.setAngle(30);
			}
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

void Map::moveRobo()
{
	auto next_pos=robo.next_coordinates();
	if(map.contains(next_pos) && map[next_pos].type!=CellType::obstacle)
	{
		robo.go();
	}
	else
	{
		std::cerr<<"Error. Obstacle is onthe way"<<std::endl;
	}
}

int Map::sonarRobo()
{
	int bit_res=0;
	auto cells=robo.sonar();
	for(auto& cell: cells)
	{
		bit_res*=2;
		if(map.contains(cell) && map[cell].type==CellType::obstacle)
		{
			bit_res++;
		}
	}
	return bit_res;
}














