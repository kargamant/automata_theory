%require "3.2"

%token <str> VAR_NAME
%token <num> LITERAL
%token <var_type> VAR_TYPE
%token ARRAY
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
	std::ofstream bison_logger("report_bison.txt");
%}

%union
{
	VarType var_type;
	std::string* str;
	int num;
}


%%
complex_statement:
	simple_statement ',' complex_statement {}
	| simple_statement '.' {}

simple_statement:
	VAR_TYPE VAR_NAME vars LEFT_ASSIGN LITERAL {
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
	| VAR_TYPE VAR_NAME vars LEFT_ASSIGN VAR_NAME
						{
						vm.pushVarToInit(*$2);
						try
						{
							vm.flushInit($1, vm.getVar(*$5)->value);
						}
						catch(std::invalid_argument error)
						{
							if(vm.getErrCode()==Err::typeMisMatch || vm.getErrCode()==Err::undefined)
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
						/*

						| ARRAY VAR_TYPE VAR_TYPE VAR_NAME '<''<' LITERAL 
						{
							Field fld{$2, $3, *$4, $7};
							vm.addArr(fld);
						}
						*/
						}
	| ARRAY VAR_TYPE VAR_TYPE VAR_NAME LEFT_ASSIGN LITERAL 
						{
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
	| VAR_NAME vars LEFT_ASSIGN VAR_NAME
						{
						vm.pushVarToInit(*$1);
						try
						{
							vm.flushAssign(vm.getVar(*$4)->value);
						}
						catch(std::invalid_argument error)
						{
							if(vm.getErrCode()==Err::typeMisMatch || vm.getErrCode()==Err::undefined)
							{
								std::cerr<<"Syntax error at line "<<@4.first_line<<std::endl;
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
	| VAR_NAME vars LEFT_ASSIGN LITERAL
						{
						vm.pushVarToInit(*$1);
						try
						{
							vm.flushAssign($4);
						}
						catch(std::invalid_argument error)
						{
							if(vm.getErrCode()==Err::typeMisMatch || vm.getErrCode()==Err::undefined)
							{
								std::cerr<<"Syntax error at line "<<@4.first_line<<std::endl;
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
	| VAR_NAME '[' LITERAL LITERAL ']' LEFT_ASSIGN LITERAL
						{
							bool isVar=true;
							try
							{
								vm.getVar(*$1);
							}
							catch(std::invalid_argument error)
							{
								isVar=false;
							}
							if(isVar && !vm.getVar(*$1)->isField)
							{
									std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
									std::cerr<<"Error. Variable "+*$1+" is not an array."<<std::endl;
							}
							else
							{
								try
								{
									Var& item=dynamic_cast<Field*>(vm.getVar(*$1))->getVar($3, $4);
									item.value=$7;
								}
								catch(std::invalid_argument error)
								{
									if(vm.getErrCode()==Err::undefined)
									{
										std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
									}
									else if(vm.getErrCode()==Err::outOfRange)
									{
										std::cerr<<"Syntax error at line "<<@3.first_line<<std::endl;
									}
									std::cerr<<"Error text: "<<error.what()<<std::endl;
									vm.setErrCode(Err::no_error);	
								}
							}
						}
	|  VAR_NAME RIGHT_ASSIGN VAR_NAME vars
						{
						vm.pushVarToInit(*$3);
						try
						{
							vm.flushAssign(vm.getVar(*$1)->value);
						}
						catch(std::invalid_argument error)
						{
							if(vm.getErrCode()==Err::typeMisMatch || vm.getErrCode()==Err::undefined)
							{
								std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
							}
							else if(vm.getErrCode()==Err::redefinition)
							{
								std::cerr<<"Syntax error at line "<<@3.first_line<<std::endl;
							}
							std::cerr<<"Error text: "<<error.what()<<std::endl;
							vm.setErrCode(Err::no_error);	
							
						}
						bison_logger<<"All vars from init queue were intialized"<<std::endl;
							
						}
	| LITERAL RIGHT_ASSIGN VAR_NAME vars
						{
						vm.pushVarToInit(*$3);
						try
						{
							vm.flushAssign($1);
						}
						catch(std::invalid_argument error)
						{
							if(vm.getErrCode()==Err::typeMisMatch || vm.getErrCode()==Err::undefined)
							{
								std::cerr<<"Syntax error at line "<<@1.first_line<<std::endl;
							}
							else if(vm.getErrCode()==Err::redefinition)
							{
								std::cerr<<"Syntax error at line "<<@3.first_line<<std::endl;
							}
							std::cerr<<"Error text: "<<error.what()<<std::endl;
							
							vm.setErrCode(Err::no_error);	
						}
						bison_logger<<"All vars from init queue were intialized"<<std::endl;
							
						}
	| LITERAL RIGHT_ASSIGN VAR_NAME '[' LITERAL LITERAL ']'
						{
							bool isVar=true;
							try
							{
								vm.getVar(*$3);
							}
							catch(std::invalid_argument error)
							{
								isVar=false;
							}
							if(isVar && !vm.getVar(*$3)->isField)
							{
									std::cerr<<"Syntax error at line "<<@3.first_line<<std::endl;
									std::cerr<<"Error. Variable "+*$3+" is not an array."<<std::endl;
							}
							else
							{
								try
								{
									Var& item=dynamic_cast<Field*>(vm.getVar(*$3))->getVar($5, $6);
									item.value=$1;
								}
								catch(std::invalid_argument error)
								{
									if(vm.getErrCode()==Err::undefined)
									{
										std::cerr<<"Syntax error at line "<<@3.first_line<<std::endl;
									}
									else if(vm.getErrCode()==Err::outOfRange)
									{
										std::cerr<<"Syntax error at line "<<@5.first_line<<std::endl;
									}
									std::cerr<<"Error text: "<<error.what()<<std::endl;
									vm.setErrCode(Err::no_error);	
								}
							}
						}
	| '@' VAR_NAME '[' LITERAL LITERAL ']' 
						{
							if(!vm.getVar(*$2)->isField)
							{
								std::cerr<<"Syntax error at line "<<@2.first_line<<std::endl;
								std::cerr<<"Error. Variable "+*$2+" is not an array."<<std::endl;
							}
							else
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
						}
	| '@' VAR_NAME
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
vars:
    	VAR_NAME vars {
				vm.pushVarToInit(*$1);
				bison_logger<<"var "<<*$1<<"pushed to init queue."<<std::endl;
			}
 	| VAR_NAME {
				vm.pushVarToInit(*$1);
				bison_logger<<"var "<<*$1<<"pushed to init queue."<<std::endl;
			}
	|		{} 

%%


void yyerror(const char *s) {
	 fprintf(stderr, "%s\n", s);
}



