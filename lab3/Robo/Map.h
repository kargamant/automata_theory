#pragma once
#include <iostream>
#include <unordered_map>
#include "Robo.h"

class Map;
enum CellType
{
	obstacle,
	ground,
	escape
};

std::string nameByType(CellType type);

struct Cell
{
	private:
		//int id;
		std::pair<int, int> coordinates;
		/*Cell* tBorder;
		Cell* bBorder;
		Cell* rtBorder;
		Cell* rbBorder;
		Cell* ltBorder;
		Cell* lbBorder;*/
		CellType type;
	public:
		Cell(CellType type=CellType::ground, int x=0, int y=0) : type(type), coordinates({x, y}) {}
		Cell(CellType type, std::pair<int, int> coordinates) : type(type), coordinates(coordinates) {}
		friend void operator<<(std::ostream& stream, Cell& cell);
		friend Map;
	//Cell(CellType type, Cell* tBorder, Cell* bBorder, Cell* rtBorder, Cell* rbBorder, Cell* ltBorder,Cell* lbBorder);
};


struct CoordHash
{
	std::size_t operator()(const std::pair<int, int>& key) const
	{
		return std::hash<int>()((key.first + key.second)* (key.first - key.second));		
	}
};

struct CoordEqual
{
	bool operator()(const std::pair<int, int>& key1, const std::pair<int, int>& key2) const
	{
		return (key1.first == key2.first) && (key1.second == key2.second);
	}
};

class Map
{
	private:
		int m, n;
		std::unordered_map<std::pair<int, int>, Cell, CoordHash, CoordEqual> map;
		Robo robo;
	public:
		Map() : m(0), n(0), map() {}
		Map(int m, int n);
		Map(const std::string& filename);
		void changeCellType(int x, int y, CellType ntype);
		void changeCellType(std::pair<int, int> xy, CellType ntype);
		void setRobo(Robo& robo);
		Robo getRobo() {return robo;}
		void moveRobo();
		void rlRobo() {robo.rl();}
		void rrRobo() {robo.rr();}
		int sonarRobo();
		void transportRobo(int x, int y); //cheating command lol
		friend Cell;
		friend void operator<<(std::ostream& stream, Map& map);
};

//void operator<<(std::ostream& stream, Cell& cell);
//void operator<<(std::ostream& stream, Map& map);

