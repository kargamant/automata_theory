#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

//todo: table with boundaries for every type
class VarMap;
struct Node;

enum VarType
{
	tiny,
	small,
	normal,
	big
};

enum class AssignType
{
	//Right is more prior
	Left,
	Right
};

enum class Err
{
	no_error,
	typeMisMatch,
	redefinition,
	undefined,
	outOfRange,
	invalidAssign,
	bruh,
	roboError
};



VarType typeByName(const std::string& type_name);
std::string nameByType(VarType type);
VarType typeByInt(int t);
int intByType(VarType type);

struct Var
{
	bool isField;
	std::string name;
	VarType type;
	int value;
	Var(VarType type=VarType::tiny, const std::string& name="a", int value=0);
	void changeValue(int nvalue);
	virtual ~Var() = default;
};

struct Field : public Var
{
	//size_type_max - amount of elements in matrix
	//value of Field itself is amount of items in one line
	VarType size_type;
	std::vector<Var*> matr;
	Field(VarType item_type=VarType::tiny, VarType size_type=VarType::tiny, const std::string& name="a", int value=0);
	void updateItems();
	Var* getVar(int ind1, int ind2);
};

struct Operand
{
	//bool isExpr;
	bool isFieldItem=false;
//	Ast* i_exe=nullptr;
//	Ast* j_exe=nullptr;
	std::string i_name;
	std::string j_name;
	int i=-1;
	int j=-1;
	bool isVar;
	Var* var;
	int value;
	Operand(int value=0) : isVar(false), var(nullptr), value(value) {}
	Operand(Var* var) : isVar(true), var(var), value(var->value) {}
	Operand(Var* var, int i, int j) : isFieldItem(true), i(i), j(j), isVar(true), var(dynamic_cast<Field*>(var)->getVar(i, j)), value(var->value) {this->var->name=var->name;}
	Operand(Var* var, const std::string& i_name, const std::string& j_name) : isFieldItem(true), i_name(i_name), j_name(j_name), isVar(true), var(dynamic_cast<Field*>(var)->getVar(0, 0)), value(var->value) {this->var->name=var->name;}
	//Operand(Var* var, Ast* i, Ast* j) : isFieldItem(true), i_exe(i), j_exe(j), isVar(true), var(dynamic_cast<Field*>(var)), value(var->value) {this->var->name=var->name;}
	void exec(VarMap* vm);
	void updateValue(VarMap* scope=nullptr);
};

struct AssignOperator
{
	Operand* left;
	Operand* right;
	AssignType type;
	AssignOperator(Operand* left, Operand* right, AssignType type) : left(left), right(right), type(type) {}
	AssignOperator(AssignType type) : left(nullptr), right(nullptr), type(type) {}
	void perform();
};

void operator<<(std::ostream& stream, Var& var);
void operator<<(std::ostream& stream, Field& arr);
void operator<<(std::ostream& stream, VarMap& vm);

class VarMap
{
	private:
		std::unordered_map<std::string, Var*> map;
		static Err err_code;
	public:
		//std::vector<Error>* errors;
		std::vector<Var> to_initialize;
		std::stack<Operand> operand_stack;
		std::queue<AssignOperator> oper_queue;
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
		bool checkIfDefined(const std::string& name);
		
		void pushVarToInit(const std::string& name);
		void pushOperand(Operand op);
		void pushOperator(AssignOperator op);
		Operand popOperand();
		void clear();

		void flushInit(VarType init_type, int value);
		void flushInit(VarType init_type, VarType size_type, int value);
		void flushAssign(int value);
		void flushAssignExpr();
		void mergeIntoVm(VarMap* nvm);

		Err getErrCode() {return err_code;}
		std::vector<Var> get_to_initialize() const {
			  return to_initialize;
		}

		std::stack<Operand> get_operand_stack() const {
			  return operand_stack;
		}

		std::queue<AssignOperator> get_oper_queue() const {
			  return oper_queue;
		}
		
		void set_to_initialize(std::vector<Var> to_initialize) {
			  this->to_initialize = to_initialize;
		}

		void set_operand_stack(std::stack<Operand> operand_stack) {
			  this->operand_stack = operand_stack;
		}

		void set_oper_queue(std::queue<AssignOperator> oper_queue) {
			  this->oper_queue = oper_queue;
		}


		VarMap& setErrCode(Err nerr_code) {err_code=nerr_code; return *this;}
		void clearBuffers();
		friend Var;
		friend Field;
		friend AssignOperator;
		friend void operator<<(std::ostream& stream, VarMap& vm);
		friend Operand;
};

