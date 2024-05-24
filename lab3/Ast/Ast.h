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

struct Node
{
	std::string name;
	nodeType type;
	Node* left;
	Node* right;
	Node(nodeType type, Node* left=nullptr, Node* right=nullptr) : type(type), left(left), right(right) {}
	virtual ~Node() {}
};

struct OperandNode : public Node
{
	Operand* operand;
	OperandNode(Operand* operand) : Node(nodeType::operand), operand(operand) {}
};

struct OperatorNode : public Node
{
	operatorType type;
	std::vector<Node*> args;
	OpertorNode(operatorType type, std::vector<Node*> args) : Node(nodeType::oper), type(type), args(args) {}
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
























