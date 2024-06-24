%require "3.2"

%nterm <st> main
%nterm <st> complex_statement
%nterm <st> simple_statement
%token <str> VAR_NAME
%token <var_type> VAR_TYPE
%token <num> LITERAL
%token ARRAY
%token UNTIL
%token DO
%token CHECK
%token BEGIN_FUNC
%token END_FUNC
%token RETURN
%token GO
%token RL
%token RR
%token SONAR

//%nterm statement_group
//%nterm <num> signed_operand
%nterm <st> args
%nterm <st> expr
%nterm <st> operand
%nterm <st> numeric_operand
%nterm <st> logic_expr
%nterm <st> expr_operand
%nterm <st> assign_expr
%nterm <st> args_to_call
%nterm <st> vars
%left '+' '-'
%left '*' '/'
%left LESS_EQUAL MORE_EQUAL
%left "<" ">"
%left LEFT_ASSIGN
%right RIGHT_ASSIGN

%code requires {
	#include <iostream>
	#include <string>
	#include "../VarMap/VarMap.h"
	#include "../Ast/Ast.h"
	#include <fstream>
}
%{
	#include "../VarMap/VarMap.h"
	#include "../Ast/Ast.h"
	#include <queue>
	#include <fstream>
	#include "../Robo/Map.h"
	#include <stack>
	int yylex(void);
	void yyerror(const char *s);

	Map labirint{"labirint.txt"};
	//labirint.changeCellType(3, 4, CellType::obstacle);
	VarMap* vm=new VarMap();
	std::stack<VarMap*> program_stack;
	std::unordered_map<std::string, Ast*> declared_funcs;
	std::ofstream bison_logger("report_bison.txt");
%}

%union
{
	VarType var_type;
	std::string* str;
	int num;
	bool logic;
	Ast* st;
	//st->setRoot(main);
}


%%
main:
    complex_statement	{
    				//ast.root=main_func;
				$$->printAst();
				std::cout<<"funcs:"<<std::endl;
				for(auto& func: declared_funcs)
				{
					func.second->printAst();
				}
				//$$->root->applyFinalExec(true);
				program_stack.push(vm);
				$$->root->applyProgramStack(&program_stack);
				$$->root->applyScope(vm);
				$$->execute();
				std::cout<<"Stack:"<<std::endl;
				while(!program_stack.empty())
				{
					std::cout<<*program_stack.top();
					std::cout<<std::endl;
					program_stack.pop();
				}
				//$$->printAst();
				//ast.printAst();
    			}
	;
complex_statement:
	simple_statement complex_statement {
						Ast* nst=new Ast();
						nst->root=new ConnectingNode(",", $1->root, $2->root);
						$$=nst;
						//ast.root=main_func;
						//main_func->execute();
						//ast.printAst();
						//ast.execute();
						}
	| simple_statement '.' {
					Ast* nst=new Ast();
					nst->root=new ConnectingNode(".", $1->root, nullptr);
					$$=nst;
					//$$=$1;
					//$$->printAst();
					//ast.root=main_func;
					//main_func->execute();
					//ast.printAst();
					//ast.execute();
				}
	;
simple_statement:
	VAR_TYPE vars LEFT_ASSIGN operand ',' {
						vm->clearBuffers();
						//vm->pushVarToInit(*$2);
						
						//std::vector<Node*> args;
						//args.push_back($5->root);
						std::vector<int> params;
						params.push_back(intByType($1));
						params.push_back(@5.first_line);
						params.push_back(@2.first_line);
						
						OperatorNode* on=new DefiningOperator(vm, $2, $4->root, params);
						
						Ast* ost=new Ast(on);

						//main_func->stmts.push_back(ost);
						//stmt_group->stmts.push_back(ost);
						//to uncomment
						//ost->execute();
						$$=ost;	
						bison_logger<<"All vars from init queue were intialized"<<std::endl;
						}
	| ARRAY VAR_TYPE VAR_TYPE vars LEFT_ASSIGN operand ','
						{
							vm->clearBuffers();
							//vm->pushVarToInit(*$4);
							
							//std::vector<Node*> args;
							//args.push_back($7->root);
							std::vector<int> params;
							params.push_back(intByType($2));
							params.push_back(intByType($3));
							params.push_back(@1.first_line);
							OperatorNode* on=new DefiningOperator(vm, $4, $6->root, params, true);
							
							Ast* ost=new Ast(on);

							//main_func->stmts.push_back(ost);
							ost->execute();
							$$=ost;	
						}
	| assign_expr 	','			
	  					{
							//std::vector<int> params;
							//params.push_back(@1.first_line);
							//OperatorNode* on=new AssigningOperator(vm, params);
							//Ast* ost=new Ast(on);
							//main_func->stmts.push_back(ost);
							//ost->execute();
							//$$->execute();
							$$=$1;
							//$$->execute();
	  					}
	| '@' operand	','			{
							Ast* ost=new Ast(new PrintValueOperator($2->root), $2);
							$$=ost;
							//main_func->stmts.push_back(ost);
							//std::cout<<$2<<std::endl;
						}
	/*|					{
							Ast* ost=new Ast();
							$$=ost;
						}*/
	| UNTIL logic_expr DO complex_statement	{
							//vm->clearBuffers();
							OperatorNode* op=new UntilOperator(vm, $2->root, $4->root);
							Ast* ost=new Ast(op);
							$$=ost;
							//ost->execute();
						}
	| CHECK logic_expr DO complex_statement {
							OperatorNode* op=new CheckOperator(vm, $2->root, $4->root);
							Ast* ost=new Ast(op);
							$$=ost;

							
						}
	| VAR_TYPE VAR_NAME args BEGIN_FUNC complex_statement END_FUNC ',' {
								OperatorNode* func=new FunctionOperator($1, *$2, $3, $5->root, vm);		
								dynamic_cast<FunctionOperator*>(func)->declared_funcs=&declared_funcs;
								if(!declared_funcs.contains(*$2)) declared_funcs.insert({*$2, new Ast(func)});
								else
								{
									std::cout<<"redeclariiiiing "<<*$2<<std::endl;
									declared_funcs[*$2]->root=func;
									
									//declared_funcs[*$2]->root->updateFunctionCalls(declared_funcs);
									//declared_funcs[*$2]->root->printNode(std::cout);
								}
								Ast* ost=new Ast();
								$$=ost;
								}
	| RETURN operand ','			{
							OperatorNode* return_stmt=new ReturnOperator($2->root);
							$$=new Ast(return_stmt);
						}
	| GO ','				{
						//	labirint.changeCellType(3, 4, CellType::obstacle);
						//	labirint.changeCellType(2, 4, CellType::obstacle);
						//	labirint.changeCellType(3, 3, CellType::obstacle);
							//labirint.changeCellType(1, 2, CellType::obstacle);
							OperatorNode* op=new GoOperator(labirint);
							op->execute();
							$$=new Ast(op);
						}
	| RR ','				{
							OperatorNode* op=new RrOperator(labirint);
							op->execute();
							$$=new Ast(op);
						}
	| RL ','				{
							OperatorNode* op=new RlOperator(labirint);
							op->execute();
							$$=new Ast(op);
						}
	/*| VAR_NAME '(' args_to_call ')' ','	{
							if(declared_funcs.contains(*$1))
							{
								FunctionOperator* fp=dynamic_cast<FunctionOperator*>(declared_funcs[*$1]->root);
								OperatorNode* op=new FunctionOperator(fp->return_type, fp->name, fp->arguments, fp->stmts, vm);
								dynamic_cast<FunctionOperator*>(op)->loadArgs($3);
								$$=new Ast(op);
							}
							else
							{
								std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
								std::cerr<<"Error text: "<<"Error. Function "+*$1+" was not declared."<<std::endl;
							}
						}*/
	;
args_to_call:
	    operand args_to_call {
					$$=new Ast($1->root, $2);
	    				
	    			}
	    | operand		{
	    				$$=$1;
	    			}
	    ;
args:
    	VAR_TYPE VAR_NAME args {
					OperandNode* op=new OperandNode(new Operand(new Var($1, *$2)));

					$$=new Ast(op, $3);
    				}
	| VAR_TYPE VAR_NAME	{
					OperandNode* op=new OperandNode(new Operand(new Var($1, *$2)));
					Ast* ost=new Ast(op);
					$$=ost;
				}
	;
assign_expr:
	operand LEFT_ASSIGN assign_expr	
					{
						std::vector<int> params;
						params.push_back(@1.first_line);
						$$=new Ast(new AssigningOperator($1->root, AssignType::Left, $3->root, vm, params));
						vm->pushOperator({AssignType::Left});	
						bison_logger<<"left_assignment"<<std::endl;
					}
	| operand RIGHT_ASSIGN assign_expr	{
						std::vector<int> params;
						params.push_back(@1.first_line);
						$$=new Ast(new AssigningOperator($1->root, AssignType::Right, $3->root, vm, params));
						
						//vm->pushOperand({$1});

						//vm->pushOperand(op);
						vm->pushOperator({AssignType::Right});	
						bison_logger<<"right_assignment"<<std::endl;
					}
	| operand			{
						$$=$1;
						//vm->pushOperand({$1});

						//vm->pushOperand(op);
						//bison_logger<<"expr"<<std::endl;	
					}
	;

operand:
	numeric_operand		{
					$$=$1;
					bison_logger<<"operand_literal: "<<$1<<std::endl;
				}
	| VAR_NAME	{
			
				if(vm->checkIfDefined(*$1))
				{
					Ast* ost=new Ast(new OperandNode(new Operand(vm->getVar(*$1))));
					$$=ost;
					bison_logger<<"operand_variable: "<<std::endl;
					bison_logger<<*vm->getVar(*$1);
					bison_logger<<std::endl;
				}
				else
				{
					Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::big, *$1, 0))));
					$$=ost;
					std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
					std::cerr<<"Error text: "<<"Error. Variable "+*$1+" was not defined."<<std::endl;
				}
			}
	| VAR_NAME '[' LITERAL LITERAL ']' {
					bool exists=vm->checkIfDefined(*$1);

					if(exists && !vm->getVar(*$1)->isField)
					{
						Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *$1, 0))));
						$$=ost;
						std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
						std::cerr<<"Error. Variable "+*$1+" is not an array."<<std::endl;
					}
					else if(exists)
					{
						bool isError=false;
						try
						{
							bison_logger<<"operand_indexed_variable: "<<std::endl;
							bison_logger<<dynamic_cast<Field*>(vm->getVar(*$1))->getVar($3, $4);
							bison_logger<<std::endl;
						}
						catch(std::invalid_argument error)
						{
							Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *$1, 0))));
							$$=ost;
							isError=true;
							std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
							std::cerr<<"Error text: "<<error.what()<<std::endl;
						}
						if(!isError)
						{
							Ast* ost=new Ast(new OperandNode(new Operand(vm->getVar(*$1), $3, $4)));
							$$=ost;
						}
					}
					else
					{
						Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *$1, 0))));
						$$=ost;
						std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
						std::cerr<<"Error text: "<<"Error. Variable "+*$1+" was not defined."<<std::endl;
					}
					
					}
	| VAR_NAME '(' args_to_call ')' {
							if(declared_funcs.contains(*$1))
							{
								FunctionOperator* fp=dynamic_cast<FunctionOperator*>(declared_funcs[*$1]->root);
								OperatorNode* op=new FunctionOperator(fp->return_type, fp->name, fp->arguments, fp->stmts, vm);
								dynamic_cast<FunctionOperator*>(op)->declared_funcs=&declared_funcs;
								dynamic_cast<FunctionOperator*>(op)->loadArgs($3);
							//	std::cout<<"func operand:"<<std::endl;
							//	fp->printNode(std::cout, 1);
								$$=new Ast(op);
							}
							else
							{
								std::cout<<"predeclaring "<<*$1<<std::endl;
								Ast* ost=new Ast(new FunctionOperator(VarType::tiny, *$1, $3, nullptr, vm));
								declared_funcs.insert({*$1, ost});
								dynamic_cast<FunctionOperator*>(declared_funcs[*$1]->root)->declared_funcs=&declared_funcs;
								$$=declared_funcs[*$1];
								std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
								std::cerr<<"Error text: "<<"Error. Function "+*$1+" was not declared."<<std::endl;
							}
						}
	| SONAR					{
							OperatorNode* op=new SonarOperator(labirint);
							$$=new Ast(op);
						}
	;
numeric_operand:
	LITERAL		{
				Ast* ost=new Ast(new OperandNode(new Operand({$1})));
				$$=ost;
			}
	| expr		{

				$$=$1;
			}
	| logic_expr	{
				$$=$1;
			}
	;
expr_operand:
	LITERAL		{
				Ast* ost=new Ast(new OperandNode(new Operand({$1})));
				$$=ost;
				bison_logger<<"operand_literal: "<<$1<<std::endl;
			}
	| VAR_NAME	{
				if(vm->checkIfDefined(*$1))
				{
					Ast* ost=new Ast(new OperandNode(new Operand(vm->getVar(*$1))));
					$$=ost;
					//$$=vm->getVar(*$1)->value;
					//vm->pushOperand({vm->getVar(*$1)});
					bison_logger<<"operand_variable: "<<std::endl;
					bison_logger<<*vm->getVar(*$1);
					bison_logger<<std::endl;
				}
				else
				{
					Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::big, *$1, 0))));
					$$=ost;
					std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
					std::cerr<<"Error text: "<<"Error. Variable "+*$1+" was not defined."<<std::endl;
				}
			}
	| VAR_NAME '[' LITERAL LITERAL ']' {
					bool exists=vm->checkIfDefined(*$1);

					if(exists && !vm->getVar(*$1)->isField)
					{
						Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *$1, 0))));
						$$=ost;
						std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
						std::cerr<<"Error. Variable "+*$1+" is not an array."<<std::endl;
					}
					else if(exists)
					{
						bool isError=false;
						try
						{
							//vm->pushOperand({vm->getVar(*$1), $3, $4});
							bison_logger<<"operand_indexed_variable: "<<std::endl;
							bison_logger<<dynamic_cast<Field*>(vm->getVar(*$1))->getVar($3, $4);
							bison_logger<<std::endl;
						}
						catch(std::invalid_argument error)
						{
							Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *$1, 0))));
							$$=ost;
							isError=true;
							if(vm->getErrCode()==Err::undefined)
							{
								std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
							}
							else if(vm->getErrCode()==Err::outOfRange)
							{
								std::cerr<<"Syntax error at line "<<@4.first_line<<std::endl;
							}
							std::cerr<<"Error text: "<<error.what()<<std::endl;
						}
						if(!isError)
						{
							//$$=dynamic_cast<Field*>(vm->getVar(*$1))->getVar($3, $4).value;
							Ast* ost=new Ast(new OperandNode(new Operand(vm->getVar(*$1), $3, $4)));
							$$=ost;
						}
					}
					else
					{
						Ast* ost=new Ast(new OperandNode(new Operand(new Var(VarType::tiny, *$1, 0))));
						$$=ost;
						std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
						std::cerr<<"Error text: "<<"Error. Variable "+*$1+" was not defined."<<std::endl;
					}
					
					}
	| VAR_NAME '(' args_to_call ')' {
							if(declared_funcs.contains(*$1))
							{
								FunctionOperator* fp=dynamic_cast<FunctionOperator*>(declared_funcs[*$1]->root);
								dynamic_cast<FunctionOperator*>(declared_funcs[*$1]->root)->declared_funcs=&declared_funcs;
								OperatorNode* op=new FunctionOperator(fp->return_type, fp->name, fp->arguments, fp->stmts, vm);
								dynamic_cast<FunctionOperator*>(op)->declared_funcs=&declared_funcs;
								dynamic_cast<FunctionOperator*>(op)->loadArgs($3);
							//	std::cout<<"func operand:"<<std::endl;
							//	fp->printNode(std::cout, 1);
								$$=new Ast(op);
							}
							else
							{
								std::cout<<"predeclaring "<<*$1<<std::endl;
								Ast* ost=new Ast(new FunctionOperator(VarType::tiny, *$1, $3, nullptr, vm));
								declared_funcs.insert({*$1, ost});
								dynamic_cast<FunctionOperator*>(declared_funcs[*$1]->root)->declared_funcs=&declared_funcs;
								std::cout<<"here declared_funcs adress: "<<dynamic_cast<FunctionOperator*>(declared_funcs[*$1]->root)->declared_funcs<<std::endl;
								$$=declared_funcs[*$1];
								std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
								std::cerr<<"Error text: "<<"Error. Function "+*$1+" was not declared."<<std::endl;
							}
						}
	;
expr:
	expr_operand			{
					$$=$1;
					//vm->popOperand();
					bison_logger<<"operand with value "<<$1<<std::endl;
					}
	| '+' expr_operand		{
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::uplus, {$2->root}), $2);
					$$=ost;

					//$$=$2;
					//vm->popOperand();
					bison_logger<<"plused operand with value "<<$2<<std::endl;
					}
	| '-' expr_operand		{
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::uminus, {$2->root}), $2);
					$$=ost;
					//vm->popOperand();
					//bison_logger<<"minused operand with value "<<-$2<<std::endl;
					}
	| expr '*' expr		{
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::mult, {$1->root, $3->root}), $1, $3);
					$$=ost;
					//$$=$1*$3;
					//vm->pushOperand($$);
					bison_logger<<"product of two expressions with value "<<$$<<std::endl;
				}
	| expr '/' expr		{
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::div, {$1->root, $3->root}), $1, $3);
					$$=ost;
					/*if($3==0)
					{
						$$=32768;
					}
					else
					{
						$$=$1/$3;
					}*/
					bison_logger<<"division of two expressions with value "<<$$<<std::endl;
					//vm->pushOperand($$);
				}
	| expr '+' expr		{
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::plus, {$1->root, $3->root}), $1, $3);
					$$=ost;
					//$$=$1+$3;
					//vm->pushOperand($$);
					bison_logger<<"sum of two expressions with value "<<$$<<std::endl;
				}
	| expr '-' expr		{
					Ast* ost=new Ast(new ArifmeticOperator(ArifmeticType::minus, {$1->root, $3->root}), $1, $3);
					$$=ost;
					//$$=$1-$3;
					//vm->pushOperand($$);
					bison_logger<<"difference between two expressions with value "<<$$<<std::endl;
				}
	| '(' expr ')'		{
					$$=$2;
					bison_logger<<"expression in brackets with value "<<$$<<std::endl;
					//vm->pushOperand($$);
				}
	;
logic_expr:
	logic_expr LESS_EQUAL logic_expr	{
					Ast* ost=new Ast(new LogicOperator(LogicType::le, {$1->root, $3->root}), $1, $3);
					$$=ost;
					//$$=$1<=$3;
					bison_logger<<$1<<"<="<<$3<<": "<<$$<<std::endl;
				}
	| logic_expr MORE_EQUAL logic_expr  {
					Ast* ost=new Ast(new LogicOperator(LogicType::me, {$1->root, $3->root}), $1, $3);
					$$=ost;
					//$$=$1>=$3;
					bison_logger<<$1<<">="<<$3<<": "<<$$<<std::endl;
				}
	| logic_expr '<' logic_expr		{
					Ast* ost=new Ast(new LogicOperator(LogicType::l, {$1->root, $3->root}), $1, $3);
					$$=ost;
					//$$=$1<$3;
					bison_logger<<$1<<"<"<<$3<<": "<<$$<<std::endl;
				}
	| logic_expr '>' logic_expr		{
					Ast* ost=new Ast(new LogicOperator(LogicType::m, {$1->root, $3->root}), $1, $3);
					$$=ost;
					//$$=$1>$3;
					bison_logger<<$1<<">"<<$3<<": "<<$$<<std::endl;
				}
	| '(' logic_expr ')'	{
					$$=$2;
					bison_logger<<"("<<$2<<")"<<std::endl;
				}
	| expr			{
					$$=$1;
					bison_logger<<"expr from logic expr"<<std::endl;
				}
	;
vars:
    	VAR_NAME vars {
				
				OperandNode* op=new OperandNode(new Operand(new Var(VarType::tiny, *$1, 0)));
				$$=new Ast(op, $2);
				//targetVec.push_back(*$1);
				//vm->pushVarToInit(*$1);
				bison_logger<<"var "<<*$1<<"pushed to init queue."<<std::endl;
			}
 	| VAR_NAME {
				OperandNode* op=new OperandNode(new Operand(new Var(VarType::tiny, *$1, 0)));		
				$$=new Ast(op);
				//targetVec.push_back(*$1);
				//vm->pushVarToInit(*$1);
				bison_logger<<"var "<<*$1<<"pushed to init queue."<<std::endl;
			}
	|		{} 
	;

%%


void yyerror(const char *s) {
	 fprintf(stderr, "%s\n", s);
}



