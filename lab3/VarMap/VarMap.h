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
	undefined,
	outOfRange	
};


VarType typeByName(const std::string& type_name);
std::string nameByType(VarType& type);

struct Var
{
	bool isField;
	std::string name;
	VarType type;
	int value;
	Var(VarType type=VarType::tiny, const std::string& name="a", int value=0);
	virtual ~Var() = default;
};

struct Field : public Var
{
	//size_type_max - amount of elements in matrix
	//value of Field itself is amount of items in one line
	VarType size_type;
	std::vector<Var> matr;
	Field(VarType item_type=VarType::tiny, VarType size_type=VarType::tiny, const std::string& name="a", int value=0);
	void updateItems();
	Var& getVar(int ind1, int ind2);
};

void operator<<(std::ostream& stream, Var& var);
void operator<<(std::ostream& stream, Field& arr);

class VarMap
{
	private:
		std::unordered_map<std::string, Var*> map;
		//std::unordered_map<std::string, Field> field_map;
		std::vector<Var> to_initialize;
		//std::vector<Field> fields_to_initialize;
		//VarType init_type;
		static Err err_code;
	public:
		~VarMap()
		{
			for(auto& v: map)
			{
				delete v.second;
			}
		}
		static std::unordered_map<VarType, int> size_table;
		
		void addVar(Var* var);
		void changeVar(const std::string& name, int val);
		Var* getVar(const std::string& name);
		
		void pushVarToInit(const std::string& name);
		void flushInit(VarType init_type, int value);
		void flushAssign(int value);
		//void flushAssignArr(int value);

		Err getErrCode() {return err_code;}
		VarMap& setErrCode(Err nerr_code) {err_code=nerr_code; return *this;}
		friend Var;
		friend Field;

};
