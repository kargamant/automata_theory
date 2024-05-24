#include "../VarMap/VarMap.h"

enum class nodeType
{
	operand,
	oper
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
	std::string name;
	nodeType type;
	Node* left;
	Node* right;
	Node(nodeType type, Node* left=nullptr, Node* right=nullptr) : type(type), left(left), right(right) {}
	virtual ~Node() {}
	virtual int execute()=0;
};

struct OperandNode : public Node
{
	Operand* operand;
	OperandNode(Operand* operand) : Node(nodeType::operand), operand(operand) {}
	int execute() override;
};

struct OperatorNode : public Node
{
	operatorType type;
	std::vector<Node*> args;
	OpertorNode(operatorType type, std::vector<Node*> args) : Node(nodeType::oper), type(type), args(args) {}
	int execute() override;
};

struct PrintValueOperator : public OperatorNode
{
	PrintOperator(Node* target) : OperatorNode(operatorType::printValue, {target}) {}	
	int execute() override;
};

struct ArifmeticOperator : public OperatorNode
{
	ArifmeticType type;
	ArifmeticOperator(ArifmeticType type, std::vector<Node*> args) : OperatorNode(operatorType::arifmetic, args) {} 
	int execute() override;
};

struct LogicOperator : public OperatorNode
{
	LogicType type;
	LogicOperator(LogicType type, std::vector<Node*> args) : OperatorNode(operatorType::logic, args) {}
	int execute() override;
};

class Ast
{
	private:
		Node* root;
	public:
		Ast(Node* root=nullptr) : root(root) {}
		Ast(Node* node, Ast& ast) : root(new Node(node->type, ast.root)) {}
		Ast(Node* node, Ast& ast1, Ast& ast2) : root(new Node(node->type, ast1.root, ast2.root)) {}

};
























