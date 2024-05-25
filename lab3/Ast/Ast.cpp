#include "Ast.h"

Ast::Ast(Node* node, Ast* ast) 
{
	root=node;
	root->left=ast->root;
	root->right=nullptr;
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
	return 0;
}

int ConnectingNode::execute()
{
	left->execute();
	right->execute();
	return 0;
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
	return 0;
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
	return 0;
}

int DefiningOperator::execute()
{
	if(isExecuted) return 0;
	try
	{
		int operand=args[0]->execute();
		if(!fieldDefine)
		{
			vm->flushInit(typeByInt(params[0]), operand);
		}
		else
		{
			vm->flushInit(typeByInt(params[0]), typeByInt(params[1]), operand);
		}
	}
	catch(std::invalid_argument error)
	{
		if(vm->getErrCode()==Err::typeMisMatch)
		{
			std::cerr<<"Syntax error at line "<<params[2]<<std::endl;
		}
		else if(vm->getErrCode()==Err::redefinition)
		{
			std::cerr<<"Syntax error at line "<<params[2]<<std::endl;
		}
		std::cerr<<"E00000rror text: "<<error.what()<<std::endl;
		vm->setErrCode(Err::no_error);	
	}
	isExecuted=true;
	return 0;
}

int AssigningOperator::execute()
{
	if(isExecuted) return 0;
	try
	{
		vm->flushAssignExpr();
	}
	catch(std::invalid_argument error)
	{
		if(vm->getErrCode()==Err::invalidAssign)
		{
			std::cerr<<"Syntax error at line "<<params[0]<<std::endl;
		}
		else if(vm->getErrCode()==Err::outOfRange)
		{
			std::cerr<<"Syntax error at line "<<params[0]<<std::endl;
		}

		std::cerr<<"Error text: "<<error.what()<<std::endl;
		vm->setErrCode(Err::no_error);	
	}
	isExecuted=true;
	return 0;	
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

void ConnectingNode::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	//if(name==".") stream<<"."<<std::endl;
	if(left!=nullptr) left->printNode(stream, spaces+4);
	if(right!=nullptr) right->printNode(stream, spaces+4);
}

void Ast::printAst(std::ostream& stream)
{
	root->printNode(stream, 0);
}

void DefiningOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<"<"<<nameByType(typeByInt(params[0]))<<"> defining with:"<<std::endl;
	args[0]->printNode(stream, spaces+6);
}

void AssigningOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<"assigning expression"<<std::endl;
}












