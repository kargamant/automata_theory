#pragma once
#include "../VarMap/VarMap.h"
#include "../Robo/Map.h"

class Ast;
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
	return_stmt,
	go,
	rl,
	rr,
	sonar
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
	Var* to_return;
	VarMap* scope=nullptr;
	bool* returnFlag=nullptr;
	bool isFinalExec=false;
	Node(nodeType type, Node* left=nullptr, Node* right=nullptr) : type(type), left(left), right(right) {}
	Node(Node* cnode);
	virtual ~Node() {}
	virtual int execute()=0;
	virtual void printNode(std::ostream& stream=std::cout, int spaces=0)=0;
	void applyScope(VarMap* nscope);
	void applyToReturn(Var* nreturn);
	void applyReturnFlag(bool* nretFlag);
	void applyFinalExec(bool nFinalExec);
	void updateFunctionCalls(std::unordered_map<std::string, Ast*>& declared_funcs);
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
	PrintValueOperator(Node* target) : OperatorNode(operatorType::printValue, {target}) {left=target;}	
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct ArifmeticOperator : public OperatorNode
{
	ArifmeticType type;
	ArifmeticOperator(ArifmeticType type, std::vector<Node*> args) : type(type), OperatorNode(operatorType::arifmetic, args) {left=args[0]; right=args[1];}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct LogicOperator : public OperatorNode
{
	LogicType type;
	LogicOperator(LogicType type, std::vector<Node*> args) : type(type), OperatorNode(operatorType::logic, args) {left=args[0]; right=args[1];}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct DefiningOperator : public OperatorNode
{
	VarMap* vm;
	std::vector<int> params;
	bool fieldDefine;
	Ast* args;
	Node* operand;
	DefiningOperator(VarMap* vm, Ast* args, Node* operand, std::vector<int> params, bool fieldDefine=false) : OperatorNode(operatorType::defineVar), vm(vm), params(params), fieldDefine(fieldDefine), args(args), operand(operand) {isExecuted=false; left=args->root; right=operand;}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;

};

struct AssigningOperator : public OperatorNode
{
	VarMap* vm;
	AssignType assign_type;
	//Node* left;
	//Node* right;
	std::vector<int> params;
	AssigningOperator(Node* left_op, AssignType type, Node* right_op, VarMap* vm, std::vector<int> params) : assign_type(type), OperatorNode(operatorType::assignExpr, {left_op, right_op}), vm(vm), params(params) {left=left_op; right=right_op;}
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
	VarMap local_scope;
	std::vector<std::string> args_order;
	Var return_value;
	bool returnMet=false;
	std::unordered_map<std::string, Ast*>* declared_funcs=nullptr;

	Node* stmts;
	FunctionOperator(VarType return_type, const std::string& name, Ast* arguments, Node* stmts, VarMap* global_scope);
	void unparseArguments();
	void loadArgs(Ast* args_to_call);
	void build();
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct ReturnOperator : public OperatorNode
{
	//VarType return_type;
	Node* value_to_return;
	ReturnOperator(Node* value_to_return) : OperatorNode(operatorType::return_stmt), value_to_return(value_to_return) {left=value_to_return;}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

struct GoOperator : public OperatorNode
{
	Map& labirint;
	GoOperator(Map& labirint) : OperatorNode(operatorType::go), labirint(labirint) {}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;

};

struct RlOperator : public OperatorNode
{
	Map& labirint;
	RlOperator(Map& labirint) : OperatorNode(operatorType::rl), labirint(labirint) {}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;

};

struct RrOperator : public OperatorNode
{
	Map& labirint;
	RrOperator(Map& labirint) : OperatorNode(operatorType::rr), labirint(labirint) {}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;

};

struct SonarOperator : public OperatorNode
{
	Map& labirint;
	SonarOperator(Map& labirint) : OperatorNode(operatorType::sonar), labirint(labirint) {}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;

};








