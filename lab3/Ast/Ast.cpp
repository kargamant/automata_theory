#include "Ast.h"

Ast::Ast(Node* node, Ast* ast) 
{
	root=node;
	root->left=ast->root;
}
Ast(Node* node, Ast* ast1, Ast* ast2) 
{
	root=node;
	root->left=ast1->root;
	root->right=ast2->root;
}
void Ast::execute()
{
	root->execute();
}
int CstmtNode::execute() override
{
	for(auto& ast: stmts)
	{
		ast->execute();
	}
}
int OperandNode::execute() override
{
	return operand->value;
}

int PrintValueOperator::execute() override
{
	if(args[0]->type==nodeType::operand) std::cout<<dynamic_cast<OperandNode*>(args[0])->operand->value<<std::endl;
	else
	{
		std::cout<<dynamic_cast<OperatorNode*>(args[0])->execute()<<std::endl;
	}
	return 0;
}

int ArifmeticOperator::execute() override
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

int LogicOperator::execute() override
{
	switch(type)
	{
		case ArifmeticType::le:
			return args[0]->execute()<=args[1]->execute();	
		case ArifmeticType::me:
			return args[0]->execute()>=args[1]->execute();
		case ArifmeticType::l:
		        return args[0]->execute()<args[1]->execute();
		case ArifmeticType::m:
		        return args[0]->execute()>args[1]->execute();
	}
}

void OperandNode::printNode(std::ostream& stream=std::cout, int spaces=0) override
{
	stream<<std::string(spaces, ' ');
	if(operand->isVar)
	{
		stream<<*operand->var;
		stream<<std::endl;
	}
	else
	{
		stream<<operand->value;
	}
}

void PrintValueOperator::printNode(std::ostream& stream=std::cout, int spaces=0) override
{
	stream<<std::string(spaces, ' ');
	stream<<"@"<<std::endl;
	left->printNode(stream, spaces+4);
}


void ArifmeticOperator::printNode(std::ostream& stream=std::cout, int spaces=0) override
{
	stream<<std::string(spaces, ' ');
	switch(type)
	{
		case ArifmeticType::plus:
			stream<<"+"<<std::endl;
			left->printNode(stream, spaces+4);
			right->printNode(stream, spaces+4);
		case ArifmeticType::minus:
			stream<<"-"<<std::endl;
			left->printNode(stream, spaces+4);
			right->printNode(stream, spaces+4);
		case ArifmeticType::div:
			stream<<"/"<<std::endl;
			left->printNode(stream, spaces+4);
			right->printNode(stream, spaces+4);
		case ArifmeticType::mult:
			stream<<"*"<<std::endl;
			left->printNode(stream, spaces+4);
			right->printNode(stream, spaces+4);
		case ArifmeticType::uminus:
			stream<<"-"<<std::endl;
			left->printNode(stream, spaces+4);
		case ArifmeticType::uplus:
			stream<<"+"<<std::endl;
			left->printNode(stream, spaces+4);
	}
	
}


void LogicOperator::printNode(std::ostream& stream=std::cout, int spaces=0) override
{
	stream<<std::string(spaces, ' ');
	switch(type)
	{
		case ArifmeticType::le:
			stream<<"<="<<std::endl;
		case ArifmeticType::me:
			stream<<"=>"<<std::endl;
		case ArifmeticType::l:
			stream<<"<"<<std::endl;
		case ArifmeticType::m:
			stream<<">"<<std::endl;
	}
	left->printNode(stream, spaces+4);
	right->printNode(stream, spaces+4);
}

void CstmtNode::printNode(std::ostream& stream=std::cout, int spaces=0) override
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













