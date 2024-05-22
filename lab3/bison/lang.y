%require "3.2"

%token <str> VAR_NAME
%token <num> LITERAL
%token <var_type> VAR_TYPE
%token ARRAY
%nterm <num> operand
%nterm <num> numeric_operand
%nterm <num> logic_expr
%nterm <num> expr
%nterm <num> expr_operand
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
	#include <fstream>
}
%{
	#include "../VarMap/VarMap.h"
	#include <fstream>
	int yylex(void);
	void yyerror(const char *s);

	VarMap vm;	
	int last_operand;
	std::vector<std::string> targetVec;
	int source_value;
	std::ofstream bison_logger("report_bison.txt");
%}

%union
{
	VarType var_type;
	std::string* str;
	int num;
	bool logic;
}


%%
complex_statement:
	simple_statement ',' complex_statement {}
	| simple_statement '.' {}

simple_statement:
	VAR_TYPE VAR_NAME vars LEFT_ASSIGN operand {
						vm.clearBuffers();
						vm.pushVarToInit(*$2);
						try
						{
							vm.flushInit($1, $5);
						}
						catch(std::invalid_argument error)
						{
							if(vm.getErrCode()==Err::typeMisMatch)
							{
								std::cerr<<"Syntax error at line "<<@5.first_line<<std::endl;
							}
							else if(vm.getErrCode()==Err::redefinition)
							{
								std::cerr<<"Syntax error at line "<<@2.first_line<<std::endl;
							}
							std::cerr<<"Error text: "<<error.what()<<std::endl;
							vm.setErrCode(Err::no_error);	
						}
						bison_logger<<"All vars from init queue were intialized"<<std::endl;
						}
	| ARRAY VAR_TYPE VAR_TYPE VAR_NAME LEFT_ASSIGN operand
						{
							vm.clearBuffers();
							//Field fld{$2, $3, *$4, $7};
							try
							{
								Var* fld=new Field($2, $3, *$4, $6);
								vm.addVar(fld);
							}
							catch(std::invalid_argument error)
							{
								
								if(vm.getErrCode()==Err::typeMisMatch)
								{
									std::cerr<<"Syntax error at line "<<@6.first_line<<std::endl;
								}
								else if(vm.getErrCode()==Err::redefinition)
								{
									std::cerr<<"Syntax error at line "<<@4.first_line<<std::endl;
								}
								std::cerr<<"Error text: "<<error.what()<<std::endl;
								vm.setErrCode(Err::no_error);	
							}
						}
	  | assign_expr 				
	  					{
							try
							{
	  							vm.flushAssignExpr();
							}
							catch(std::invalid_argument error)
							{
								if(vm.getErrCode()==Err::invalidAssign)
								{
									std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
								}
								else if(vm.getErrCode()==Err::outOfRange)
								{
									std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
								}

								std::cerr<<"Error text: "<<error.what()<<std::endl;
								vm.setErrCode(Err::no_error);	
							}
	  					}
	| '@' operand				{
							std::cout<<$2<<std::endl;
						}
	| '$' VAR_NAME '[' LITERAL LITERAL ']' 
						{
							bool exists=vm.checkIfDefined(*$2);

							if(exists && !vm.getVar(*$2)->isField)
							{
								std::cerr<<"Syntax error at line "<<@2.first_line<<std::endl;
								std::cerr<<"Error. Variable "+*$2+" is not an array."<<std::endl;
							}
							else if(exists)
							{
								try
								{
									std::cout<<dynamic_cast<Field*>(vm.getVar(*$2))->getVar($4, $5);
									std::cout<<std::endl;
								}
								catch(std::invalid_argument error)
								{
									if(vm.getErrCode()==Err::undefined)
									{
										std::cerr<<"Syntax error at line "<<@2.first_line<<std::endl;
									}
									else if(vm.getErrCode()==Err::outOfRange)
									{
										std::cerr<<"Syntax error at line "<<@4.first_line<<std::endl;
									}
									std::cerr<<"Error text: "<<error.what()<<std::endl;
									vm.setErrCode(Err::no_error);	
								}
							}
							else
							{
								std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
								std::cerr<<"Error text: "<<"Error. Variable "+*$2+" was not defined."<<std::endl;
							}
						}
	| '$' VAR_NAME
			{
				Var* var;
				bool isError=false;
				try
				{
					var=vm.getVar(*$2);
				}
				catch(std::invalid_argument error)
				{
					isError=true;
					std::cerr<<"Syntax error at line "<<@2.first_line<<std::endl;
					std::cerr<<"Error text: "<<error.what()<<std::endl;
					vm.setErrCode(Err::no_error);	
				}
				if(!isError) 
				{
					if(var->isField)
					{
						std::cout<<(*dynamic_cast<Field*>(var));
					}
					else
					{	
						std::cout<<(*var);
					}
					std::cout<<std::endl;
				}
			}
	;
assign_expr:
	operand LEFT_ASSIGN assign_expr	
					{
						vm.pushOperator({AssignType::Left});	
						bison_logger<<"left_assignment"<<std::endl;
					}
	| operand RIGHT_ASSIGN assign_expr	{
						//vm.pushOperand({$1});

						//vm.pushOperand(op);
						vm.pushOperator({AssignType::Right});	
						bison_logger<<"right_assignment"<<std::endl;
					}
	| operand			{
						//vm.pushOperand({$1});

						//vm.pushOperand(op);
						//bison_logger<<"expr"<<std::endl;	
					}
	;
operand:
	numeric_operand		{
					$$=$1;
					vm.pushOperand({$1});
					bison_logger<<"operand_literal: "<<$1<<std::endl;
				}
	| VAR_NAME	{
			
				if(vm.checkIfDefined(*$1))
				{
					$$=vm.getVar(*$1)->value;
					vm.pushOperand({vm.getVar(*$1)});
					bison_logger<<"operand_variable: "<<std::endl;
					bison_logger<<*vm.getVar(*$1);
					bison_logger<<std::endl;
				}
				else
				{
					$$=0;
					std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
					std::cerr<<"Error text: "<<"Error. Variable "+*$1+" was not defined."<<std::endl;
				}
			}
	| VAR_NAME '[' LITERAL LITERAL ']' {
					bool exists=vm.checkIfDefined(*$1);

					if(exists && !vm.getVar(*$1)->isField)
					{
						$$=0;
						std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
						std::cerr<<"Error. Variable "+*$1+" is not an array."<<std::endl;
					}
					else if(exists)
					{
						bool isError=false;
						try
						{
							vm.pushOperand({vm.getVar(*$1), $3, $4});
							bison_logger<<"operand_indexed_variable: "<<std::endl;
							bison_logger<<dynamic_cast<Field*>(vm.getVar(*$1))->getVar($3, $4);
							bison_logger<<std::endl;
						}
						catch(std::invalid_argument error)
						{
							$$=0;
							isError=true;
							if(vm.getErrCode()==Err::undefined)
							{
								std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
							}
							else if(vm.getErrCode()==Err::outOfRange)
							{
								std::cerr<<"Syntax error at line "<<@4.first_line<<std::endl;
							}
							std::cerr<<"Error text: "<<error.what()<<std::endl;
						}
						if(!isError)
						{
							$$=dynamic_cast<Field*>(vm.getVar(*$1))->getVar($3, $4).value;
						}
					}
					else
					{
						$$=0;
						std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
						std::cerr<<"Error text: "<<"Error. Variable "+*$1+" was not defined."<<std::endl;
					}
					
					}
	;
numeric_operand:
	LITERAL		{
				$$=$1;
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
				$$=$1;
				//vm.pushOperand({$1});
				bison_logger<<"operand_literal: "<<$1<<std::endl;
			}
	| VAR_NAME	{
			
				if(vm.checkIfDefined(*$1))
				{
					$$=vm.getVar(*$1)->value;
					//vm.pushOperand({vm.getVar(*$1)});
					bison_logger<<"operand_variable: "<<std::endl;
					bison_logger<<*vm.getVar(*$1);
					bison_logger<<std::endl;
				}
				else
				{
					$$=0;
					std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
					std::cerr<<"Error text: "<<"Error. Variable "+*$1+" was not defined."<<std::endl;
				}
			}
	| VAR_NAME '[' LITERAL LITERAL ']' {
					bool exists=vm.checkIfDefined(*$1);

					if(exists && !vm.getVar(*$1)->isField)
					{
						$$=0;
						std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
						std::cerr<<"Error. Variable "+*$1+" is not an array."<<std::endl;
					}
					else if(exists)
					{
						bool isError=false;
						try
						{
							//vm.pushOperand({vm.getVar(*$1), $3, $4});
							bison_logger<<"operand_indexed_variable: "<<std::endl;
							bison_logger<<dynamic_cast<Field*>(vm.getVar(*$1))->getVar($3, $4);
							bison_logger<<std::endl;
						}
						catch(std::invalid_argument error)
						{
							$$=0;
							isError=true;
							if(vm.getErrCode()==Err::undefined)
							{
								std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
							}
							else if(vm.getErrCode()==Err::outOfRange)
							{
								std::cerr<<"Syntax error at line "<<@4.first_line<<std::endl;
							}
							std::cerr<<"Error text: "<<error.what()<<std::endl;
						}
						if(!isError)
						{
							$$=dynamic_cast<Field*>(vm.getVar(*$1))->getVar($3, $4).value;
						}
					}
					else
					{
						$$=0;
						std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
						std::cerr<<"Error text: "<<"Error. Variable "+*$1+" was not defined."<<std::endl;
					}
					
					}
	;
expr:
	expr_operand			{
					$$=$1;
					//vm.popOperand();
					bison_logger<<"operand with value "<<$1<<std::endl;
				}
	| expr '*' expr		{
					$$=$1*$3;
					//vm.pushOperand($$);
					bison_logger<<"product of two expressions with value "<<$$<<std::endl;
				}
	| expr '/' expr		{
					if($3==0)
					{
						$$=32768;
					}
					else
					{
						$$=$1/$3;
					}
					bison_logger<<"division of two expressions with value "<<$$<<std::endl;
					//vm.pushOperand($$);
				}
	| expr '+' expr		{
					$$=$1+$3;
					//vm.pushOperand($$);
					bison_logger<<"sum of two expressions with value "<<$$<<std::endl;
				}
	| expr '-' expr		{
					$$=$1-$3;
					//vm.pushOperand($$);
					bison_logger<<"difference between two expressions with value "<<$$<<std::endl;
				}
	| '(' expr ')'		{
					$$=$2;
					bison_logger<<"expression in brackets with value "<<$$<<std::endl;
					//vm.pushOperand($$);
				}
	;
logic_expr:
	logic_expr LESS_EQUAL logic_expr	{
					$$=$1<=$3;
					bison_logger<<$1<<"<="<<$3<<": "<<$$<<std::endl;
				}
	| logic_expr MORE_EQUAL logic_expr  {
					$$=$1>=$3;
					bison_logger<<$1<<">="<<$3<<": "<<$$<<std::endl;
				}
	| logic_expr '<' logic_expr		{
					$$=$1<$3;
					bison_logger<<$1<<"<"<<$3<<": "<<$$<<std::endl;
				}
	| logic_expr '>' logic_expr		{
					$$=$1>$3;
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
				//targetVec.push_back(*$1);
				vm.pushVarToInit(*$1);
				bison_logger<<"var "<<*$1<<"pushed to init queue."<<std::endl;
			}
 	| VAR_NAME {
				//targetVec.push_back(*$1);
				vm.pushVarToInit(*$1);
				bison_logger<<"var "<<*$1<<"pushed to init queue."<<std::endl;
			}
	|		{} 
	;

%%


void yyerror(const char *s) {
	 fprintf(stderr, "%s\n", s);
}



