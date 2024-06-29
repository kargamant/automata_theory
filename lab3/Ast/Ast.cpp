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
	//if(scope!=nullptr) nscope->mergeIntoVm(scope);
	//else scope=nscope;
	
	//scope=nscope;
	
	if(this->type==nodeType::oper && dynamic_cast<OperatorNode*>(this)->type==operatorType::func)
	{
		//int biba=0;
		//scope=&dynamic_cast<FunctionOperator*>(this)->local_scope;
		dynamic_cast<FunctionOperator*>(this)->arguments->root->applyScope(nscope);
		//scope=new VarMap();
		//nscope->mergeIntoVm(scope);
		//scope=&dynamic_cast<FunctionOperator*>(this)->local_scope;
	}
	else 
	{
		//scope=new VarMap();
		scope=nscope;
		//nscope->mergeIntoVm(scope);
		//std::cout<<"scope after merging:"<<std::endl;
		//std::cout<<*scope;
		//std::cout<<std::endl;
	}
	//if(this->type!=nodeType::oper || (this->type==nodeType::oper && dynamic_cast<OperatorNode*>(this)->type!=operatorType::func)) scope=nscope;
	//scope=new VarMap;
	//nscope->mergeIntoVm(scope);
	/*if(this->type==nodeType::oper && dynamic_cast<OperatorNode*>(this)->type==operatorType::func)
	{
		nscope->mergeIntoVm(scope);
		//nscope->mergeIntoVm(&dynamic_cast<FunctionOperator*>(this)->local_scope);
	}
	else
	{
		scope=nscope;
	}*/
	if(left!=nullptr) left->applyScope(nscope);
	if(right!=nullptr) right->applyScope(nscope);
}

void Node::applyErrors(std::vector<Error>* err_vec)
{
	errors=err_vec;

	if(left!=nullptr) left->applyErrors(err_vec);
	if(right!=nullptr) right->applyErrors(err_vec);
}

void Node::applyProgramStack(std::stack<VarMap*>* prog_stack)
{
	program_stack=prog_stack;
	//if(type==nodeType::oper && dynamic_cast<OperatorNode*>(this)->type==operatorType::func) dynamic_cast<FunctionOperator*>(this)->program_stack=prog_stack;
	if(left!=nullptr) left->applyProgramStack(prog_stack);
	if(right!=nullptr) right->applyProgramStack(prog_stack);
}

void Node::applyToReturn(Var* nreturn)
{
	to_return=nreturn;
	//if(this->type!=nodeType::oper || (this->type==nodeType::oper && dynamic_cast<OperatorNode*>(this)->type!=operatorType::func)) to_return=nreturn;
	if(left!=nullptr) left->applyToReturn(nreturn);
	if(right!=nullptr) right->applyToReturn(nreturn);
}

void Node::applyReturnFlag(bool* nretFlag)
{
	if(this->type==nodeType::oper && dynamic_cast<OperatorNode*>(this)->type==operatorType::func)
	{
		int biba=0;
		//returnFlag=&dynamic_cast<FunctionOperator*>(this)->returnMet;
	}
	else returnFlag=nretFlag;
	//if(this->type!=nodeType::oper || (this->type==nodeType::oper && dynamic_cast<OperatorNode*>(this)->type!=operatorType::func)) returnFlag=nretFlag;
	if(left!=nullptr) left->applyReturnFlag(nretFlag);
	if(right!=nullptr) right->applyReturnFlag(nretFlag);
}
void Node::applyFinalExec(bool nFinalExec)
{
	isFinalExec=nFinalExec;
	if(left!=nullptr) left->applyFinalExec(nFinalExec);
	if(right!=nullptr) right->applyFinalExec(nFinalExec);
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
		if(v==nullptr)
		{
			throw std::invalid_argument("Error. Function "+name+" was not defined and was tried to be called with literals.");
		}
		args_order.push_back(v->name);
		try
		{
			local_scope.addVar(new Var(v->type, v->name, v->value));
		}
		catch(std::invalid_argument)
		{
			local_scope.addVar(new Var(v->type, v->name, VarMap::size_table[v->type]-1));
			local_scope.changeVar(v->name, v->value);
		}
		ptr=ptr->left;
	}
}

void FunctionOperator::loadArgs(Ast* args_to_call)
{
	Node* ptr=args_to_call->root;
	int k=0;
	while(ptr!=nullptr)
	{
		//std::cout<<args_order[k]<<std::endl;
		/*if(dynamic_cast<OperandNode*>(ptr)->operand->isVar) 
		{
			dynamic_cast<OperandNode*>(ptr)->operand->updateValue();
		}
		std::cout<<dynamic_cast<OperandNode*>(ptr)->operand->value<<std::endl;*/
		//scope printing
		/*if(ptr->scope!=nullptr)
		{
			std::cout<<"scope: "<<std::endl;
			std::cout<<*ptr->scope;
		}*/
		/*if(ptr->type==nodeType::operand)
		{
			std::cout<<"value of ptr: "<<dynamic_cast<OperandNode*>(ptr)->operand->var->value<<std::endl;
		}*/
		try
		{
			local_scope.changeVar(args_order[k], ptr->execute());
		}
		catch(std::invalid_argument)
		{
			local_scope.addVar(new Var(VarType::big, args_order[k], ptr->execute()));
		}
		//std::cout<<local_scope.getVar(args_order[k])->value<<std::endl;
	//	if(scope==nullptr) local_scope.changeVar(args_order[k], dynamic_cast<OperandNode*>(ptr)->execute());
	//	else 
	//	{
	//		local_scope.changeVar(args_order[k], dynamic_cast<OperandNode*>(ptr)->execute());
	//		scope->changeVar(args_order[k], dynamic_cast<OperandNode*>(ptr)->execute());
	//	}
		//std::cout<<ptr->execute()<<std::endl;
		ptr=ptr->left;
		k++;
	}
	arguments=args_to_call;
}

void Node::updateFunctionCalls(std::unordered_map<std::string, Ast*>& declared_funcs)
{
	bool isUpdated=false;
	if(type==nodeType::oper)
	{
		if(dynamic_cast<OperatorNode*>(this)->type==operatorType::func)
		{
			if(declared_funcs.contains(dynamic_cast<FunctionOperator*>(this)->name))
			{
				dynamic_cast<FunctionOperator*>(this)->return_type=dynamic_cast<FunctionOperator*>(declared_funcs[dynamic_cast<FunctionOperator*>(this)->name]->root)->return_type;
				//dynamic_cast<FunctionOperator*>(this)->arguments=dynamic_cast<FunctionOperator*>(declared_funcs[dynamic_cast<FunctionOperator*>(this)->name]->root)->arguments;
				dynamic_cast<FunctionOperator*>(this)->global_scope=dynamic_cast<FunctionOperator*>(declared_funcs[dynamic_cast<FunctionOperator*>(this)->name]->root)->global_scope;
				dynamic_cast<FunctionOperator*>(this)->local_scope=dynamic_cast<FunctionOperator*>(declared_funcs[dynamic_cast<FunctionOperator*>(this)->name]->root)->local_scope;
				dynamic_cast<FunctionOperator*>(this)->args_order=dynamic_cast<FunctionOperator*>(declared_funcs[dynamic_cast<FunctionOperator*>(this)->name]->root)->args_order;
				dynamic_cast<FunctionOperator*>(this)->return_value=dynamic_cast<FunctionOperator*>(declared_funcs[dynamic_cast<FunctionOperator*>(this)->name]->root)->return_value;
				dynamic_cast<FunctionOperator*>(this)->stmts=dynamic_cast<FunctionOperator*>(declared_funcs[dynamic_cast<FunctionOperator*>(this)->name]->root)->stmts;
				isUpdated=true;
			}
		}
	}
	if(left!=nullptr) left->updateFunctionCalls(declared_funcs);
	if(right!=nullptr) right->updateFunctionCalls(declared_funcs);
//	left=dynamic_cast<FunctionOperator*>(this)->arguments->root;
//	right=dynamic_cast<FunctionOperator*>(this)->stmts;
}

void FunctionOperator::build()
{
	//std::cout<<"is nullptr???: "<<(declared_funcs==nullptr)<<std::endl;
	if(declared_funcs->contains(name))
	{
		return_type=dynamic_cast<FunctionOperator*>((*declared_funcs)[name]->root)->return_type;
		return_value=Var(return_type, "return", return_value.value);

		std::vector<int> passed_values;
		Node* ptr=arguments->root;
		while(ptr!=nullptr)
		{
			//passed_values.push_back(dynamic_cast<OperandNode*>(ptr)->operand->value);
			passed_values.push_back(ptr->execute());
			ptr=ptr->left;
		}
		//arguments=dynamic_cast<FunctionOperator*>((*declared_funcs)[name]->root)->arguments;
		int k=0;
		ptr=dynamic_cast<FunctionOperator*>((*declared_funcs)[name]->root)->arguments->root;
		local_scope=VarMap();
		while(ptr!=nullptr)
		{
			//dynamic_cast<OperandNode*>(ptr)->operand->value=passed_values[k];
			//dynamic_cast<OperandNode*>(ptr)->operand->var->changeValue(passed_values[k]);
			Var* v=dynamic_cast<OperandNode*>(ptr)->operand->var;
			try
			{
				local_scope.addVar(new Var(v->type, v->name, passed_values[k]));
			}
			catch(std::invalid_argument)
			{
				local_scope.addVar(new Var(v->type, v->name, VarMap::size_table[v->type]-1));
				local_scope.changeVar(v->name, passed_values[k]);

			}
			std::cout<<"passed value: "<<passed_values[k]<<std::endl;

			ptr=ptr->left;
			k++;
		}
		/*Node* old_args=arguments->root;
		arguments=dynamic_cast<FunctionOperator*>((*declared_funcs)[name]->root)->arguments;
		
		Node* ptr=old_args;
		Node* nptr=arguments->root;
		while(ptr!=nullptr)
		{
			dynamic_cast<OperandNode*>(ptr)->operand->var->type=dynamic_cast<OperandNode*>(nptr)->operand->var->type;
			if(dynamic_cast<OperandNode*>(ptr)->operand->var->name!=dynamic_cast<OperandNode*>(nptr)->operand->var->name)
			{
				
			}
			ptr=ptr->left;
			nptr=nptr->left;
		}*/
		
		stmts=dynamic_cast<FunctionOperator*>((*declared_funcs)[name]->root)->stmts;
	}
	else
	{
		//errors->push_back(Error(Err::undefined, "Error. Function \""+name+"\" was not defined.", this));
		throw std::invalid_argument("Error. Function \""+name+"\" was not defined.");
	}
}

int FunctionOperator::execute()
{
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
	//if(returnMet) return to_return->value;
	//std::cout<<"is prog stack null???: "<<(program_stack==nullptr)<<std::endl;
	/*std::stack<VarMap*> copy_stack=*program_stack;
				std::cout<<"Stack before func call:"<<std::endl;
				while(!copy_stack.empty())
				{
					std::cout<<*copy_stack.top();
					std::cout<<std::endl;
					copy_stack.pop();
				}*/
	//arguments->root->applyScope(&local_scope);
	std::cout<<"local scope before anything:"<<std::endl;
	std::cout<<local_scope;
	arguments->root->applyProgramStack(program_stack);
	loadArgs(arguments);
	//std::cout<<"local scope lol:"<<std::endl;
	//std::cout<<local_scope;
	build();
	std::cout<<"local scope after build:"<<std::endl;
	std::cout<<local_scope;
	//if(declared_funcs!=nullptr) stmts->updateFunctionCalls(*declared_funcs);


	
	stmts->applyScope(&local_scope);
	/*if(scope==nullptr) 
	{
		//scope=&local_scope;
		stmts->applyScope(&local_scope);
	}
	else 
	{
		//merge local scope into scope without redeclarations
		//local_scope.mergeIntoVm(scope);
		stmts->applyScope(scope);
	}*/
	
//	
//	if(scope!=nullptr)
//	{
//		std::cout<<"scope: "<<std::endl;
//		std::cout<<*scope;
//	}
	VarMap* copy_scope=new VarMap;
	*copy_scope=local_scope;
	program_stack->push(copy_scope);
	std::stack<VarMap*> copy_stack=*program_stack;
				std::cout<<"Stack after push:"<<std::endl;
				while(!copy_stack.empty())
				{
					std::cout<<*copy_stack.top();
					std::cout<<std::endl;
					copy_stack.pop();
				}
	stmts->applyProgramStack(program_stack);
	stmts->applyToReturn(&return_value);
	returnMet=false;
	stmts->applyErrors(errors);
	stmts->applyReturnFlag(&returnMet);
	int actual_res=stmts->execute();
	//std::cout<<"f("<<local_scope.getVar("n")->value<<")=="<<actual_res<<std::endl;
	//std::cout<<"actual res: "<<actual_res<<std::endl;
	program_stack->pop();
	copy_stack=*program_stack;
				std::cout<<"Stack after exec and pop:"<<std::endl;
				while(!copy_stack.empty())
				{
					std::cout<<*copy_stack.top();
					std::cout<<std::endl;
					copy_stack.pop();
				}
	Var v=Var(return_type, "", 0);
	v.changeValue(actual_res);
	//return return_value.value;
	return v.value;
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
		//std::cout<<"local scope return:"<<std::endl;
		//std::cout<<local_scope;
		
		/*if(scope!=nullptr)
		{
			std::cout<<"scope return: "<<std::endl;
			std::cout<<*scope;
		}*/
		int res=value_to_return->execute();
		to_return->value=res;
		*returnFlag=true;
		return res;
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
			//std::cout<<"return from left "<<res<<std::endl;
			to_return->changeValue(res);
			return res;
		}
		if(right==nullptr && returnFlag!=nullptr && *returnFlag) return to_return->value;
	}
	if(right!=nullptr) 
	{
		int res=right->execute();
		if(right->type==nodeType::oper && dynamic_cast<OperatorNode*>(right)->type==operatorType::return_stmt)
		{
			//std::cout<<"return from right "<<res<<std::endl;
			to_return->changeValue(res);
			return res;
		}
		if(returnFlag!=nullptr && *returnFlag) return to_return->value;
	}
	return 0;
}

int OperandNode::execute()
{
	if(program_stack!=nullptr && !program_stack->empty())
	{
		bool isSuccesful=false;
		std::stack<VarMap*> copy_stack=*program_stack;
		while(!isSuccesful)
		{
			bool error=false;
			try
			{
				//operand->updateValue(scope);
				if(copy_stack.empty()) break;
				operand->updateValue(copy_stack.top());
			}
			catch(std::invalid_argument)
			{
				error=true;
				//some interesting edit
				if(copy_stack.empty()) break;
				copy_stack.pop();
			}
			if(!error) isSuccesful=true;
			else break;
		}
		if(!isSuccesful)
		{
			try
			{
				operand->updateValue(scope);
			}
			catch(std::invalid_argument error)
			{
				errors->push_back(Error(scope->getErrCode(), error.what(), this));
			}
		}
	}
	else
	{
		try
		{
			operand->updateValue(scope);
		}
		catch(std::invalid_argument error)
		{
			errors->push_back(Error(scope->getErrCode(), error.what(), this));
		}
	}
	return operand->value;
}

int PrintValueOperator::execute()
{
//	std::cout<<"JUST TO CHECK: "<<std::endl;
//	std::cout<<dynamic_cast<Field*>(program_stack->top()->getVar("ff"))->getVar(0, 0)->value<<std::endl;
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
	if(args[0]->type==nodeType::operand) 
	{
		dynamic_cast<OperandNode*>(args[0])->operand->updateValue(program_stack->top());
		//dynamic_cast<OperandNode*>(args[0])->operand->updateValue(scope);
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
	//int out=-1;
	int a=-1;
	int b=-1;
	Node* anode;
	Node* bnode;
	switch(type)
	{
		case ArifmeticType::plus:
			anode=args[0];
			bnode=args[1];
			a=anode->execute();
			b=bnode->execute();
			std::cout<<"f(n-1) f(n-2): "<<a<<" "<<b<<std::endl;
			return a+b;	
		case ArifmeticType::minus:
			return args[0]->execute()-args[1]->execute();
		case ArifmeticType::div:
			a=args[0]->execute();
			b=args[1]->execute();
			if(b==0)
			{
				if(a>=0) return VarMap::size_table[VarType::big];
				else return -VarMap::size_table[VarType::big];
			}
			else
			{
				return a/b;
			}
		        //return args[0]->execute()/args[1]->execute();
		case ArifmeticType::mult:
			/*std::cout<<"fac(b) a before calc: "<<a<<" "<<b<<std::endl;
			if(scope!=nullptr)
			{
				std::cout<<"scope: "<<std::endl;
				std::cout<<*scope;
			}*/
			a=args[0]->execute();
			b=args[1]->execute();
			//std::cout<<"fac(b) a: "<<a<<" "<<b<<std::endl;
			/*if(scope!=nullptr)
			{
				std::cout<<"scope: "<<std::endl;
				std::cout<<*scope;
			}*/
			//std::cout<<"product: "<<a<<" * "<<b<<std::endl;
			//out=args[0]->execute()*args[1]->execute();
			//std::cout<<"out: "<<out<<std::endl;
		        return a*b;
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
					//std::cout<<"operand: "<<operand->execute()<<std::endl;
					program_stack->top()->addVar(new Var(vtype, vname, operand->execute()));
					//scope->addVar(new Var(vtype, vname, operand->execute()));
					//std::cout<<"defined ";
					//std::cout<<*scope->getVar(vname);
					//std::cout<<std::endl;
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
					if(!isExecuted) program_stack->top()->addVar(new Field(vtype, stype, vname, operand->execute()));
				}
				else
				{
					program_stack->top()->addVar(new Field(vtype, stype, vname, operand->execute()));
				}
				ptr=ptr->left;
			}
			//vm->flushInit(typeByInt(params[0]), typeByInt(params[1]), operand);
		}
	}
	catch(std::invalid_argument error)
	{
		errors->push_back(Error(program_stack->top()->getErrCode(), error.what(), this));
		//to uncomment
		/*if(vm->getErrCode()==Err::typeMisMatch)
		{
			std::cerr<<"Syntax error at line "<<params[2]<<std::endl;
		}
		else if(vm->getErrCode()==Err::redefinition)
		{
			std::cerr<<"Syntax error at line "<<params[2]<<std::endl;
		}
		std::cerr<<"E00000rror text: "<<error.what()<<std::endl;*/
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
			errors->push_back(Error(Err::invalidAssign, "Error. You cant assign anything to not operand.", this));
			//std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
			//std::cerr<<"Error. You cant assign anything to not operand."<<std::endl;
			return 1;
		}
		else if(!dynamic_cast<OperandNode*>(left)->operand->isVar)
		{
			errors->push_back(Error(Err::invalidAssign, "Error. Cant assign anything to literal. It's not a memory.", this));
			//std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
			//std::cerr<<"Error. Cant assign anything to literal. It's not a memory."<<std::endl;
		}
		else
		{
			if(right->type==nodeType::operand)
			{
				try
				{
				//	std::cout<<"scopchik: "<<std::endl;
				//	std::cout<<*program_stack->top();
					dynamic_cast<OperandNode*>(left)->operand->var->changeValue(dynamic_cast<OperandNode*>(right)->execute());
				//	std::cout<<"scopchik: "<<std::endl;
				//	std::cout<<*program_stack->top();
					dynamic_cast<OperandNode*>(left)->operand->value=dynamic_cast<OperandNode*>(right)->execute();
					
					//else dynamic_cast<Field*>(dynamic_cast<OperandNode*>(left)->operand->var)->getVar(dynamic_cast<OperandNode*>(left)->operand->i, dynamic_cast<OperandNode*>(left)->operand->j)->value=dynamic_cast<OperandNode*>(right)->execute();
					
					if(program_stack!=nullptr && !dynamic_cast<OperandNode*>(left)->operand->isFieldItem) program_stack->top()->changeVar(dynamic_cast<OperandNode*>(left)->operand->var->name, dynamic_cast<OperandNode*>(right)->execute());
					else if(program_stack!=nullptr) dynamic_cast<Field*>(program_stack->top()->getVar(dynamic_cast<OperandNode*>(left)->operand->var->name))->getVar(dynamic_cast<OperandNode*>(left)->operand->i, dynamic_cast<OperandNode*>(left)->operand->j)->value=dynamic_cast<OperandNode*>(right)->execute();

				//	std::cout<<"scopchik: "<<std::endl;
				//	std::cout<<*program_stack->top();

					return dynamic_cast<OperandNode*>(left)->execute();
				}catch(std::invalid_argument error)
				{
					errors->push_back(Error(vm->getErrCode(), error.what(), this));
					//errors->push_back(Error(Err::undefined, error.what(), this));
				}
			}
			else
			{
			//	try
			//	{
					int execution=right->execute();
					dynamic_cast<OperandNode*>(left)->operand->var->changeValue(execution);	
					dynamic_cast<OperandNode*>(left)->operand->value=execution;
					if(program_stack!=nullptr) program_stack->top()->changeVar(dynamic_cast<OperandNode*>(left)->operand->var->name, execution);
			//	}
			//	catch(std::invalid_argument error)
			//	{
			//		errors->push_back(Error(vm->getErrCode(), error.what(), this));
			//	}
				return dynamic_cast<OperandNode*>(left)->operand->value;
			}
		}
	}
	else
	{
		if(right->type!=nodeType::operand && right->type!=nodeType::oper)
		{
			errors->push_back(Error(Err::invalidAssign, "Error. You cant assign anything to not operand.", this));
		//	std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
		//	std::cerr<<"Error. You cant assign anything to not operand."<<std::endl;
			return 1;
		}
		else if(right->type==nodeType::operand && !dynamic_cast<OperandNode*>(right)->operand->isVar)
		{
			errors->push_back(Error(Err::invalidAssign, "Error. Cant assign anything to literal. It's not a memory.", this));
		//	std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
		//	std::cerr<<"Error. Cant assign anything to literal. It's not a memory."<<std::endl;
		}
		else
		{
			if(left->type==nodeType::operand)
			{
				if(right->type==nodeType::operand)
				{
					try
					{
						dynamic_cast<OperandNode*>(right)->operand->var->changeValue(dynamic_cast<OperandNode*>(left)->execute());	
						dynamic_cast<OperandNode*>(right)->operand->value=dynamic_cast<OperandNode*>(left)->execute();

						if(program_stack!=nullptr) program_stack->top()->changeVar(dynamic_cast<OperandNode*>(right)->operand->var->name, dynamic_cast<OperandNode*>(left)->execute());
					}
					catch(std::invalid_argument error)
					{
						errors->push_back(Error(vm->getErrCode(), error.what(), this));
					}
					return dynamic_cast<OperandNode*>(right)->operand->value;
				}
				else
				{
					
					if(dynamic_cast<OperatorNode*>(right)->type!=operatorType::assignExpr)
					{
						errors->push_back(Error(Err::invalidAssign, "Error. You cant assign anything to result of some operator, because it is literal.", this));
					//	std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
					//	std::cerr<<"Error. You cant assign anything to result of some operator, because it is literal."<<std::endl;
						return 1;
					}
					else if(dynamic_cast<AssigningOperator*>(right)->left->type!=nodeType::operand)
					{
						errors->push_back(Error(Err::invalidAssign, "Error. You cant assign anything to not operand.", this));
					//	std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
					//	std::cerr<<"Error. You cant assign anything to not operand."<<std::endl;
						return 1;
					}
					else if(dynamic_cast<AssigningOperator*>(right)->left->type==nodeType::operand && !dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->isVar)
					{
						errors->push_back(Error(Err::invalidAssign, "Error. Cant assign anything to literal. It's not a memory.", this));
					//	std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
					//	std::cerr<<"Error. Cant assign anything to literal. It's not a memory."<<std::endl;
						return 1;
					}
					else
					{
					//	try
					//	{
							dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->var->changeValue(dynamic_cast<OperandNode*>(left)->execute());
							dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->value=dynamic_cast<OperandNode*>(left)->execute();

							if(program_stack!=nullptr) program_stack->top()->changeVar(dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->var->name, dynamic_cast<OperandNode*>(left)->execute());
							//int temp=dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->value;
							right->execute();
					//	}
					//	catch(std::invalid_argument error)
					//	{
					//		errors->push_back(Error(vm->getErrCode(), error.what(), this));
					//	}
						//return temp;
						return dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->value;
					}
				}
			}
			else
			{
			//	try
			//	{
				int execution=left->execute();
			//	} catch(std::invalid_argument error)
			//	{
			//		errors->push_back(Error(vm->getErrCode(), error.what(), this));
			//	}
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
						errors->push_back(Error(Err::invalidAssign, "Error. You cant assign anything to result of some operator, because it is literal.", this));
					//	std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
					//	std::cerr<<"Error. You cant assign anything to result of some operator, because it is literal."<<std::endl;
						return 1;
					}
					else if(dynamic_cast<AssigningOperator*>(right)->left->type!=nodeType::operand)
					{
						errors->push_back(Error(Err::invalidAssign, "Error. You cant assign anything to not operand.", this));
					//	std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
					//	std::cerr<<"Error. You cant assign anything to not operand."<<std::endl;
						return 1;
					}
					else if(dynamic_cast<AssigningOperator*>(right)->left->type==nodeType::operand && !dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->isVar)
					{
						errors->push_back(Error(Err::invalidAssign, "Error. Cant assign anything to literal. It's not a memory.", this));
					//	std::cerr<<"Syntax error at "<<params[0]<<" line"<<std::endl;
					//	std::cerr<<"Error. Cant assign anything to literal. It's not a memory."<<std::endl;
						return 1;
					}
					else
					{
					//	try
					//	{
							dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->var->changeValue(execution);
							dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->value=execution;

							if(program_stack!=nullptr) program_stack->top()->changeVar(dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->var->name, execution);
							int temp=dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->value;
							right->execute();
					//	}catch(std::invalid_argument error)
					//	{
					//		errors->push_back(Error(vm->getErrCode(), error.what(), this));
					//	}
						return temp;
						//return dynamic_cast<OperandNode*>(dynamic_cast<AssigningOperator*>(right)->left)->operand->value;
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
	int old_err_size=errors->size();
	while(!expr->execute())
	{		
		if(old_err_size!=errors->size())
		{
			break;
		}
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
		if(returnFlag!=nullptr && *returnFlag) return to_return->value;
	}
	return 0;
}

int GoOperator::execute()
{
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
//	if(isFinalExec)
//	{
	try
	{
		labirint.moveRobo();
		std::cout<<labirint;
		std::cout<<std::endl;
	}
	catch(std::invalid_argument error)
	{
		errors->push_back(Error(Err::roboError, error.what(), this));
	}
//	}
	return 0;
}
int RrOperator::execute()
{
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
//	if(isFinalExec)
//	{
		labirint.rrRobo();
		std::cout<<labirint;
		std::cout<<std::endl;
//	}
	return 0;
}
int RlOperator::execute()
{
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
//	if(isFinalExec)
//	{
		labirint.rlRobo();
		std::cout<<labirint;
		std::cout<<std::endl;
//	}
	return 0;
}
int SonarOperator::execute()
{
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
	std::cout<<labirint;
	std::cout<<std::endl;
	return labirint.sonarRobo();
}
int CompassOperator::execute()
{
	if(returnFlag!=nullptr && *returnFlag) return to_return->value;
	std::cout<<labirint;
	std::cout<<std::endl;
	return labirint.compass();
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
		if(dynamic_cast<OperandNode*>(ptr)->operand->isVar)
		{
			stream<<nameByType(dynamic_cast<OperandNode*>(ptr)->operand->var->type)<<" ";
			stream<<dynamic_cast<OperandNode*>(ptr)->operand->var->name<<", ";
		}
		else
		{
			stream<<ptr->execute()<<std::endl;
		}
		ptr=ptr->left;
	}
	stream<<") "<<std::endl;
	stream<<"begin"<<std::endl;
	if(stmts!=nullptr) stmts->printNode(stream, spaces+4);
	stream<<"end"<<std::endl;
}

void ReturnOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	stream<<"return ";
	value_to_return->printNode(stream, 0);
}

void GoOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	stream<<"go operation in labirint:"<<std::endl;
	stream<<labirint;
	stream<<std::endl;
}

void RrOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	stream<<"rr operation in labirint:"<<std::endl;
	stream<<labirint;
	stream<<std::endl;
}

void RlOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	stream<<"rl operation in labirint:"<<std::endl;
	stream<<labirint;
	stream<<std::endl;
}

void SonarOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	stream<<"sonar operation in labirint:"<<std::endl;
	stream<<labirint;
	stream<<std::endl;
}

void CompassOperator::printNode(std::ostream& stream, int spaces)
{
	stream<<std::string(spaces, ' ');
	stream<<"compass operation in labirint:"<<std::endl;
	stream<<labirint;
	stream<<std::endl;
}

void operator<<(std::ostream& stream, Error& err)
{
	stream<<"Run time error:"<<std::endl;
	stream<<"Error text: "<<err.err_text<<std::endl;
	stream<<"Node guilty:"<<std::endl;
	//if(err.guilty!=nullptr) err.guilty->printNode(stream);
}


