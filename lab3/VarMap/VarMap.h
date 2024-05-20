#pragma once
#include <unordered_map>
#include <string>
#include <iostream>

enum class VarType
{
	tiny,
	small,
	normal,
	big
};

VarType typeByName(const std::string& type_name);
std::string nameByType(VarType& type);

struct Var
{
	std::string name;
	VarType type;
	int value;
	Var(VarType type=VarType::tiny, const std::string& name="a", int value=0) : type(type), name(name), value(value) {}
};

void operator<<(std::ostream& stream, Var& var);

//struct Field

class VarMap
{
	private:
		std::unordered_map<std::string, Var> map;
	public:
		void addVar(Var var);
		void changeVar(const std::string& name, int val);
		Var getVar(const std::string& name);
};
