#pragma once
#include "../VarMap/VarMap.h"

enum class nodeType
{
	operand,
	oper,
	cstmt,
	connecting
};

enum class operatorType
{
	defineVar,
	indexedVar,
	assignExpr,
	printValue,
	printVar,
	arifmetic,
	logic,
	until,
	check,
	func,
	return_stmt
};

enum class ArifmeticType
{
	plus,
	minus,
	uminus,
	uplus,
	div,
	mult
};

enum class LogicType
{
	le,
	me,
	l,
	m
};

struct Node
{
	nodeType type;
	Node* left=nullptr;
	Node* right=nullptr;
	VarMap* scope=nullptr;
	Node(nodeType type, Node* left=nullptr, Node* right=nullptr) : type(type), left(left), right(right) {}
	virtual ~Node() {}
	virtual int execute()=0;
	virtual void printNode(std::ostream& stream=std::cout, int spaces=0)=0;
	void applyScope(VarMap* nscope);
};


class Ast
{
	public:
		Node* root;
		Ast(Node* root=nullptr) : root(root) {}
		Ast(Node* node, Ast* ast);
		Ast(Node* node, Ast* ast1, Ast* ast2);
		void printAst(std::ostream& stream=std::cout);
		int execute();
};


struct CstmtNode : public Node
{
	std::string func_name;
	VarMap vm;
	std::vector<Ast*> stmts;
	CstmtNode(std::vector<Ast*> stmts, std::string func_name) : Node(nodeType::cstmt), stmts(stmts), func_name(func_name) {}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct OperandNode : public Node
{
	Operand* operand;
	OperandNode(Operand* operand) : Node(nodeType::operand), operand(operand) {}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct OperatorNode : public Node
{
	bool isExecuted=false;
	operatorType type;
	std::vector<Node*> args;
	VarMap* args_scope;
	OperatorNode(operatorType type, std::vector<Node*> args) : Node(nodeType::oper), type(type), args(args) {}
	OperatorNode(operatorType type) : Node(nodeType::oper), type(type) {}
	//int execute() override;
	//void printNode(std::ostream& stream=std::cout, int spaces=0);
	//virtual ~OperatorNode() {}
};

struct ConnectingNode : public Node
{
	std::string name;
	ConnectingNode(const std::string& name, Node* left=nullptr, Node* right=nullptr) : Node(nodeType::connecting, left, right), name(name) {}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct PrintValueOperator : public OperatorNode
{
	PrintValueOperator(Node* target) : OperatorNode(operatorType::printValue, {target}) {}	
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct ArifmeticOperator : public OperatorNode
{
	ArifmeticType type;
	ArifmeticOperator(ArifmeticType type, std::vector<Node*> args) : type(type), OperatorNode(operatorType::arifmetic, args) {} 
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct LogicOperator : public OperatorNode
{
	LogicType type;
	LogicOperator(LogicType type, std::vector<Node*> args) : type(type), OperatorNode(operatorType::logic, args) {}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct DefiningOperator : public OperatorNode
{
	VarMap* vm;
	std::vector<int> params;
	bool fieldDefine;
	DefiningOperator(VarMap* vm, std::vector<Node*> args, std::vector<int> params, bool fieldDefine=false) : OperatorNode(operatorType::defineVar, args), vm(vm), params(params), fieldDefine(fieldDefine) {}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;

};

struct AssigningOperator : public OperatorNode
{
	VarMap* vm;
	AssignType assign_type;
	Node* left;
	Node* right;
	std::vector<int> params;
	AssigningOperator(Node* left, AssignType type, Node* right, VarMap* vm, std::vector<int> params) : left(left), right(right), assign_type(type), OperatorNode(operatorType::assignExpr, {left, right}), vm(vm), params(params) {}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct UntilOperator : public OperatorNode
{
	Node* expr;
	Node* stmts;
	VarMap* vm;
	UntilOperator(VarMap* vm, Node* expr, Node* stmts) :vm(vm), OperatorNode(operatorType::until, {expr, stmts}), expr(expr), stmts(stmts) {left=expr; right=stmts;}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct CheckOperator : public OperatorNode
{
	Node* expr;
	Node* stmts;
	VarMap* vm;
	CheckOperator(VarMap* vm, Node* expr, Node* stmts) :vm(vm), OperatorNode(operatorType::check, {expr, stmts}), expr(expr), stmts(stmts) {left=expr; right=stmts;}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct FunctionOperator : public OperatorNode
{
	VarType return_type;
	std::string name;
	Ast* arguments;
	VarMap* global_scope;
	VarMap scope;
	std::vector<std::string> args_order;

	Node* stmts;
	FunctionOperator(VarType return_type, const std::string& name, Ast* arguments, Node* stmts, VarMap* global_scope);
	void unparseArguments();
	void loadArgs(Ast* args_to_call);
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct ReturnOperator : public OperatorNode
{
	//VarType return_type;
	Node* value_to_return;
	ReturnOperator(Node* value_to_return) : OperatorNode(operatorType::return_stmt), value_to_return(value_to_return) {}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};













