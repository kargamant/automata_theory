#include "Ast.h"

Ast::Ast(Node* node, Ast* ast) 
{
	root=node;
	root->left=ast->root;
}
Ast::Ast(Node* node, Ast* ast1, Ast* ast2) 
{
	root=node;
	root->left=ast1->root;
	root->right=ast2->root;
}
void Ast::execute()
{
	root->execute();
}
int CstmtNode::execute()
{
	for(auto& ast: stmts)
	{
		ast->execute();
	}
}
int OperandNode::execute()
{
	return operand->value;
}

int PrintValueOperator::execute()
{
	if(args[0]->type==nodeType::operand) std::cout<<dynamic_cast<OperandNode*>(args[0])->operand->value<<std::endl;
	else
	{
		std::cout<<dynamic_cast<OperatorNode*>(args[0])->execute()<<std::endl;
	}
	return 0;
}

int ArifmeticOperator::execute()
{
	switch(type)
	{
		case ArifmeticType::plus:
			return args[0]->execute()+args[1]->execute();	
		case ArifmeticType::minus:
			return args[0]->execute()-args[1]->execute();
		case ArifmeticType::div:
		        return args[0]->execute()/args[1]->execute();
		case ArifmeticType::mult:
		        return args[0]->execute()*args[1]->execute();
		case ArifmeticType::uminus:
			return -args[0]->execute();
		case ArifmeticType::uplus:
			return args[0]->execute();
	}
}

int LogicOperator::execute()
{
	switch(type)
	{
		case LogicType::le:
			return args[0]->execute()<=args[1]->execute();	
		case LogicType::me:
			return args[0]->execute()>=args[1]->execute();
		case LogicType::l:
		        return args[0]->execute()<args[1]->execute();
		case LogicType::m:
		        return args[0]->execute()>args[1]->execute();
	}
}

void OperandNode::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	if(operand->isVar)
	{
		stream<<*operand->var;
		stream<<std::endl;
	}
	else
	{
		stream<<operand->value<<std::endl;
	}
}

void PrintValueOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	stream<<"@"<<std::endl;
	left->printNode(stream, spaces+4);
}


void ArifmeticOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	switch(type)
	{
		case ArifmeticType::plus:
			stream<<"+"<<std::endl;
			left->printNode(stream, spaces+4);
			right->printNode(stream, spaces+4);
			break;
		case ArifmeticType::minus:
			stream<<"-"<<std::endl;
			left->printNode(stream, spaces+4);
			right->printNode(stream, spaces+4);
			break;
		case ArifmeticType::div:
			stream<<"/"<<std::endl;
			left->printNode(stream, spaces+4);
			right->printNode(stream, spaces+4);
			break;
		case ArifmeticType::mult:
			stream<<"*"<<std::endl;
			left->printNode(stream, spaces+4);
			right->printNode(stream, spaces+4);
			break;
		case ArifmeticType::uminus:
			stream<<"-"<<std::endl;
			left->printNode(stream, spaces+4);
			break;
		case ArifmeticType::uplus:
			stream<<"+"<<std::endl;
			left->printNode(stream, spaces+4);
			break;
	}
	
}


void LogicOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	switch(type)
	{
		case LogicType::le:
			stream<<"<="<<std::endl;
			break;
		case LogicType::me:
			stream<<"=>"<<std::endl;
			break;
		case LogicType::l:
			stream<<"<"<<std::endl;
			break;
		case LogicType::m:
			stream<<">"<<std::endl;
			break;
	}
	left->printNode(stream, spaces+4);
	right->printNode(stream, spaces+4);
}

void CstmtNode::printNode(std::ostream& stream, int spaces)
{
	stream<<"function "<<func_name<<std::endl;
	for(auto& ast: stmts)
	{
		ast->printAst(stream);
	}
}

void Ast::printAst(std::ostream& stream)
{
	root->printNode(stream, 0);
}












