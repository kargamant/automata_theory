#include "Ast.h"

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
