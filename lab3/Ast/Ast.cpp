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

//TOdo: FINISH this func
void Node::applyScope(VarMap* nscope)
{
	scope=nscope;
	if(left!=nullptr) left->applyScope(nscope);
	if(right!=nullptr) right->applyScope(nscope);
}

void Node::applyToReturn(Var* nreturn)
{
	to_return=nreturn;
	if(left!=nullptr) left->applyToReturn(nreturn);
	if(right!=nullptr) right->applyToReturn(nreturn);
}

void Node::applyReturnFlag(bool* nretFlag)
{
	returnFlag=nretFlag;
	if(left!=nullptr) left->applyReturnFlag(nretFlag);
	if(right!=nullptr) right->applyReturnFlag(nretFlag);
}

FunctionOperator::FunctionOperator(VarType return_type, const std::string& name, Ast* arguments, Node* stmts, VarMap* global_scope) : OperatorNode(operatorType::func), return_type(return_type), name(name), arguments(arguments), stmts(stmts), global_scope(global_scope)
{
	left=arguments->root;
	right=stmts;
	//defines argument names in local scope
	unparseArguments();
	return_value=Var(return_type, "return", 0);
}

void FunctionOperator::unparseArguments()
{
	Node* ptr=arguments->root;
	while(ptr!=nullptr)
	{
		Var* v=dynamic_cast<OperandNode*>(ptr)->operand->var;
		args_order.push_back(v->name);
		scope.addVar(new Var(v->type, v->name, v->value));
		ptr=ptr->left;
	}
}

void FunctionOperator::loadArgs(Ast* args_to_call)
{
	Node* ptr=args_to_call->root;
	int k=0;
	while(ptr!=nullptr)
	{
		std::cout<<args_order[k]<<std::endl;
		/*if(dynamic_cast<OperandNode*>(ptr)->operand->isVar) 
		{
			dynamic_cast<OperandNode*>(ptr)->operand->updateValue();
		}
		std::cout<<dynamic_cast<OperandNode*>(ptr)->operand->value<<std::endl;*/
		scope.changeVar(args_order[k], dynamic_cast<OperandNode*>(ptr)->execute());
		std::cout<<ptr->execute()<<std::endl;
		ptr=ptr->left;
		k++;
	}
}

int FunctionOperator::execute()
{
	stmts->applyScope(&scope);
	stmts->applyToReturn(&return_value);
	returnMet=false;
	stmts->applyReturnFlag(&returnMet);
	stmts->execute();
	return return_value.value;
}

int ReturnOperator::execute()
{
//	if(value_to_return->type!=nodeType::operand)
//	{
//		std::cerr<<"Error. Cant return anything but operand type."<<std::endl;
//		return 0;
//	}
//	else
//	{
		*returnFlag=true;
		return value_to_return->execute();
//	}
}

int Ast::execute()
{
	return root->execute();
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
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
	if(left!=nullptr) 
	{
		int res=left->execute();
		if(left->type==nodeType::oper && dynamic_cast<OperatorNode*>(left)->type==operatorType::return_stmt)
		{
			std::cout<<"return from left "<<res<<std::endl;
			to_return->changeValue(res);
			return res;
		}
	}
	if(right!=nullptr) 
	{
		int res=right->execute();
		if(right->type==nodeType::oper && dynamic_cast<OperatorNode*>(right)->type==operatorType::return_stmt)
		{
			std::cout<<"return from right "<<res<<std::endl;
			to_return->changeValue(res);
			return res;
		}
	}
	return 0;
}

int OperandNode::execute()
{
	operand->updateValue(scope);
	return operand->value;
}

int PrintValueOperator::execute()
{
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
	if(args[0]->type==nodeType::operand) 
	{
		dynamic_cast<OperandNode*>(args[0])->operand->updateValue(scope);
		std::cout<<dynamic_cast<OperandNode*>(args[0])->operand->value<<std::endl;
	}
	else
	{
		std::cout<<dynamic_cast<OperatorNode*>(args[0])->execute()<<std::endl;
	}
	return 0;
}

int ArifmeticOperator::execute()
{
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
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
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
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
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
	//if(isExecuted) return 0;
	try
	{
		int operand_value=operand->execute();
		if(!fieldDefine)
		{
			Node* ptr=args->root;
			while(ptr!=nullptr)
			{
				VarType vtype=typeByInt(params[0]);
				std::string vname=dynamic_cast<OperandNode*>(ptr)->operand->var->name;
				
				if(scope==nullptr)
				{
					//std::cout<<"operand value: "<<dynamic_cast<OperandNode*>(ptr)->operand->value<<std::endl;
					if(!isExecuted) vm->addVar(new Var(vtype, vname, operand->execute()));
				}
				else
				{
					std::cout<<"operand: "<<operand->execute()<<std::endl;
					scope->addVar(new Var(vtype, vname, operand->execute()));
					std::cout<<"defined ";
					std::cout<<*scope->getVar(vname);
					std::cout<<std::endl;
				}
				ptr=ptr->left;
			}
			//vm->flushInit(typeByInt(params[0]), operand);
		}
		else
		{
			Node* ptr=args->root;
			while(ptr!=nullptr)
			{
				VarType vtype=typeByInt(params[0]);
				VarType stype=typeByInt(params[1]);
				std::string vname=dynamic_cast<OperandNode*>(ptr)->operand->var->name;
				
				if(scope==nullptr)
				{
					if(!isExecuted) vm->addVar(new Field(vtype, stype, vname, operand->execute()));
				}
				else
				{
					scope->addVar(new Field(vtype, stype, vname, operand->execute()));
				}
				ptr=ptr->left;
			}
			//vm->flushInit(typeByInt(params[0]), typeByInt(params[1]), operand);
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
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
	if(assign_type==AssignType::Left)
	{
		if(left->type!=nodeType::operand)
		{
			std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
			std::cerr<<"Error. You cant assign anything to not operand."<<std::endl;
			return 1;
		}
		else if(!dynamic_cast<OperandNode*>(left)->operand->isVar)
		{
			std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
			std::cerr<<"Error. Cant assign anything to literal. It's not a memory."<<std::endl;
		}
		else
		{
			if(right->type==nodeType::operand)
			{
				dynamic_cast<OperandNode*>(left)->operand->var->changeValue(dynamic_cast<OperandNode*>(right)->execute());	
				dynamic_cast<OperandNode*>(left)->operand->value=dynamic_cast<OperandNode*>(right)->execute();
				if(scope!=nullptr) scope->changeVar(dynamic_cast<OperandNode*>(left)->operand->var->name, dynamic_cast<OperandNode*>(right)->execute());
				return dynamic_cast<OperandNode*>(left)->execute();
			}
			else
			{
				int execution=right->execute();
				dynamic_cast<OperandNode*>(left)->operand->var->changeValue(execution);	
				dynamic_cast<OperandNode*>(left)->operand->value=execution;
				if(scope!=nullptr) scope->changeVar(dynamic_cast<OperandNode*>(left)->operand->var->name, execution);
				return dynamic_cast<OperandNode*>(left)->operand->value;
			}
		}
	}
	else
	{
		if(right->type!=nodeType::operand && right->type!=nodeType::oper)
		{
			std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
			std::cerr<<"Error. You cant assign anything to not operand."<<std::endl;
			return 1;
		}
		else if(right->type==nodeType::operand && !dynamic_cast<OperandNode*>(right)->operand->isVar)
		{
			std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
			std::cerr<<"Error. Cant assign anything to literal. It's not a memory."<<std::endl;
		}
		else
		{
			if(left->type==nodeType::operand)
			{
				if(right->type==nodeType::operand)
				{
					dynamic_cast<OperandNode*>(right)->operand->var->changeValue(dynamic_cast<OperandNode*>(left)->execute());	
					dynamic_cast<OperandNode*>(right)->operand->value=dynamic_cast<OperandNode*>(left)->execute();

					if(scope!=nullptr) scope->changeVar(dynamic_cast<OperandNode*>(right)->operand->var->name, dynamic_cast<OperandNode*>(left)->execute());
					return dynamic_cast<OperandNode*>(right)->operand->value;
				}
				else
				{
					
					if(dynamic_cast<OperatorNode*>(right)->type!=operatorType::assignExpr)
					{
						std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
						std::cerr<<"Error. You cant assign anything to result of some operator, because it is literal."<<std::endl;
						return 1;
					}
					else if(dynamic_cast<AssigningOperator*>(right)->left->type!=nodeType::operand)
					{
						std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
						std::cerr<<"Error. You cant assign anything to not operand."<<std::endl;
						return 1;
					}
					else if(dynamic_cast<AssigningOperator*>(right)->left->type==nodeType::operand && !dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->isVar)
					{
						std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
						std::cerr<<"Error. Cant assign anything to literal. It's not a memory."<<std::endl;
						return 1;
					}
					else
					{
						dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->var->changeValue(dynamic_cast<OperandNode*>(left)->execute());
						dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->value=dynamic_cast<OperandNode*>(left)->execute();

						if(scope!=nullptr) scope->changeVar(dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->var->name, dynamic_cast<OperandNode*>(left)->execute());
						return dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->value;
					}
				}
			}
			else
			{
				int execution=left->execute();
				if(right->type==nodeType::operand)
				{
					dynamic_cast<OperandNode*>(right)->operand->var->changeValue(execution);	
					dynamic_cast<OperandNode*>(right)->operand->value=execution;
					return dynamic_cast<OperandNode*>(right)->operand->value;
				}
				else
				{
					if(dynamic_cast<OperatorNode*>(right)->type!=operatorType::assignExpr)
					{
						std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
						std::cerr<<"Error. You cant assign anything to result of some operator, because it is literal."<<std::endl;
						return 1;
					}
					else if(dynamic_cast<AssigningOperator*>(right)->left->type!=nodeType::operand)
					{
						std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
						std::cerr<<"Error. You cant assign anything to not operand."<<std::endl;
						return 1;
					}
					else if(dynamic_cast<AssigningOperator*>(right)->left->type==nodeType::operand && !dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->isVar)
					{
						std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
						std::cerr<<"Error. Cant assign anything to literal. It's not a memory."<<std::endl;
						return 1;
					}
					else
					{
						dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->var->changeValue(execution);
						dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->value=execution;

						if(scope!=nullptr) scope->changeVar(dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->var->name, execution);
						return dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->value;
					}
				}
			}
		}
	}
	return 0;	
}

int UntilOperator::execute()
{
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
	while(!expr->execute())
	{
		
		stmts->execute();
		
	//	if(expr->type==nodeType::oper) dynamic_cast<OperatorNode*>(expr)->isExecuted=false;
	//	if(stmts->left!=nullptr && stmts->left->type==nodeType::oper) dynamic_cast<OperatorNode*>(stmts->left)->isExecuted=false;
	//	if(stmts->right!=nullptr && stmts->right->type==nodeType::oper) dynamic_cast<OperatorNode*>(stmts->right)->isExecuted=false;
		
	}
	return 0;
}

int CheckOperator::execute()
{
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
	if(expr->execute())
	{
		stmts->execute();
		
		if(expr->type==nodeType::oper) dynamic_cast<OperatorNode*>(expr)->isExecuted=false;
		if(stmts->left!=nullptr && stmts->left->type==nodeType::oper) dynamic_cast<OperatorNode*>(stmts->left)->isExecuted=false;
		if(stmts->right!=nullptr && stmts->right->type==nodeType::oper) dynamic_cast<OperatorNode*>(stmts->right)->isExecuted=false;
	}
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
	stream<<std::string(spaces, ' ');
	stream<<"<"<<nameByType(typeByInt(params[0]))<<"> defining with:"<<std::endl;
	operand->printNode(stream, spaces+6);
}

void AssigningOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	if(assign_type==AssignType::Left) stream<<"<<"<<std::endl;
	else stream<<">>"<<std::endl;
	left->printNode(stream, spaces+8);
	right->printNode(stream, spaces+8);
}

void UntilOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	stream<<"until "<<std::endl;
	expr->printNode();
	stream<<" do "<<std::endl;
	stmts->printNode();
}


void CheckOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	stream<<"check "<<std::endl;
	expr->printNode();
	stream<<"do "<<std::endl;
	stmts->printNode();
}

void FunctionOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<nameByType(return_type)<<" "<<name<<" (";
	Node* ptr=arguments->root;
	while(ptr!=nullptr)
	{
		stream<<nameByType(dynamic_cast<OperandNode*>(ptr)->operand->var->type)<<" ";
		stream<<dynamic_cast<OperandNode*>(ptr)->operand->var->name<<", ";
		ptr=ptr->left;
	}
	stream<<") "<<std::endl;
	stream<<"begin"<<std::endl;
	stmts->printNode(stream, spaces+4);
	stream<<"end"<<std::endl;
}

void ReturnOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	stream<<"return ";
	value_to_return->printNode(stream, 0);
}




