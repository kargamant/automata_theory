#pragma once
#include "../VarMap/VarMap.h"

enum class nodeType
{
	operand,
	oper,
	cstmt
};

enum class operatorType
{
	defineVar,
	defineArray,
	indexedVar,
	assignExpr,
	printValue,
	printVar,
	arifmetic,
	logic
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
	Node* left;
	Node* right;
	Node(nodeType type, Node* left=nullptr, Node* right=nullptr) : type(type), left(left), right(right) {}
	virtual ~Node() {}
	virtual int execute()=0;
	virtual void printNode(std::ostream& stream=std::cout, int spaces=0)=0;
};


class Ast
{
	public:
		Node* root;
		Ast(Node* root=nullptr) : root(root) {}
		Ast(Node* node, Ast* ast);
		Ast(Node* node, Ast* ast1, Ast* ast2);
		void printAst(std::ostream& stream=std::cout);
		void execute();
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
	operatorType type;
	std::vector<Node*> args;
	OperatorNode(operatorType type, std::vector<Node*> args) : Node(nodeType::oper), type(type), args(args) {}
	//int execute() override;
	//void printNode(std::ostream& stream=std::cout, int spaces=0);
	//virtual ~OperatorNode() {}
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
	LogicOperator(LogicType type, std::vector<Node*> args) : OperatorNode(operatorType::logic, args) {}
	int execute() override;
	void printNode(std::ostream& stream=std::cout, int spaces=0) override;
};

























