#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>

//todo: table with boundaries for every type

enum class VarType
{
	tiny,
	small,
	normal,
	big
};

enum class Err
{
	no_error,
	typeMisMatch,
	redefinition,
	undefined
};


VarType typeByName(const std::string& type_name);
std::string nameByType(VarType& type);

struct Var
{
	std::string name;
	VarType type;
	int value;
	Var(VarType type=VarType::tiny, const std::string& name="a", int value=0);
};

/*struct Field
{
	VarType item_type;
	VarType size_type;
	std::string name;
	std::vector<>
};*/

void operator<<(std::ostream& stream, Var& var);

class VarMap
{
	private:
		std::unordered_map<std::string, Var> map;
		std::vector<Var> to_initialize;
		//VarType init_type;
		static Err err_code;
	public:
		static std::unordered_map<VarType, int> size_table;
		void addVar(Var var);
		void changeVar(const std::string& name, int val);
		Var getVar(const std::string& name);
		void pushVarToInit(const std::string& name);
		void flushInit(VarType init_type, int value);
		void flushAssign(int value);
		Err getErrCode() {return err_code;}
		//VarMap& setInitType(VarType type) {init_type=type; return *this;}
		friend Var;

};
