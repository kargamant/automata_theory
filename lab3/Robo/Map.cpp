#include "Map.h"
#include <vector>
#include <fstream>
#include <cmath>


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
				escape.first=i;
				escape.second=j;
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
		throw std::invalid_argument("Error. Obstacle is onthe way");
	}
}

int Map::sonarRobo()
{
	if(map[robo.getCoordinates()].type==CellType::escape) return -1;
	int bit_res=0;
	auto cells=robo.sonar();
	for(auto& cell: cells)
	{
		bit_res*=2;
		if((map.contains(cell) && map[cell].type==CellType::obstacle) || !map.contains(cell))
		{
			bit_res++;
		}
	}
	return bit_res;
}

int Map::compass()
{
	//std::cout<<"ESCAPE: "<<escape.first<<" "<<escape.second<<std::endl;
	double tg=(double)(escape.first-robo.getX())/(double)(escape.second-robo.getY());
	int angle=std::atan(tg)*180/M_PI;

	if(robo.getX()<escape.first && robo.getY()>escape.second)
	{
		return 180-angle;
	}
	else if(robo.getX()<escape.first && robo.getY()<escape.second)
	{
		return 360-angle;
	}
	else if(robo.getX()>escape.first && robo.getY()<escape.second)
	{
		return -angle;
	}
	else if(robo.getX()>escape.first && robo.getY()>escape.second)
	{
		return 180-angle;
	}
	else
	{
		if(robo.getX()==escape.first && robo.getY()==escape.second) return 0;
		else if(robo.getX()==escape.first)
		{
			if(robo.getY()>escape.second) return 180;
			else return 0;
		}
		else
		{
			if(robo.getX()<escape.first) return 270;
			else return 90;
		}
	}
	//std::cout<<"TANGENS: "<<tg<<std::endl;
}

void Map::transportRobo(int x, int y)
{
	robo.setCoordinates({x, y});
}













