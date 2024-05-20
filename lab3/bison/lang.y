%require "3.2"

%token <str> VAR_NAME
%token <num> LITERAL
%token <var_type> VAR_TYPE
%token ARRAY

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
	VAR_TYPE VAR_NAME vars '<''<' LITERAL {
						vm.pushVarToInit(*$2);
						try
						{
							vm.flushInit($1, $6);
						}
						catch(std::invalid_argument error)
						{
							if(vm.getErrCode()==Err::typeMisMatch)
							{
								std::cerr<<"Syntax error at "<<@6.first_line<<":"<<@6.first_column<<":"<<@6.last_line<<":"<<@6.last_column<<std::endl;
							}
							else if(vm.getErrCode()==Err::redefinition)
							{
								std::cerr<<"Syntax error at "<<@2.first_line<<":"<<@2.first_column<<":"<<@2.last_line<<":"<<@2.last_column<<std::endl;
							}
							std::cerr<<"Error text: "<<error.what()<<std::endl;
							
						}
						bison_logger<<"All vars from init queue were intialized"<<std::endl;
						}
	| VAR_TYPE VAR_NAME vars '<''<' VAR_NAME
						{
						vm.pushVarToInit(*$2);
						try
						{
							vm.flushInit($1, vm.getVar(*$6).value);
						}
						catch(std::invalid_argument error)
						{
							if(vm.getErrCode()==Err::typeMisMatch || vm.getErrCode()==Err::undefined)
							{
								std::cerr<<"Syntax error at "<<@6.first_line<<":"<<@6.first_column<<":"<<@6.last_line<<":"<<@6.last_column<<std::endl;
							}
							else if(vm.getErrCode()==Err::redefinition)
							{
								std::cerr<<"Syntax error at "<<@2.first_line<<":"<<@2.first_column<<":"<<@2.last_line<<":"<<@2.last_column<<std::endl;
							}
							std::cerr<<"Error text: "<<error.what()<<std::endl;
							
						}
						bison_logger<<"All vars from init queue were intialized"<<std::endl;
							
						}
	| ARRAY VAR_TYPE VAR_TYPE VAR_NAME vars '<''<' LITERAL 
						{
							
						}
	| '@' VAR_NAME
			{
				Var var;
				bool isError=false;
				try
				{
					var=vm.getVar(*$2);
				}
				catch(std::invalid_argument error)
				{
					isError=true;
					std::cerr<<"Syntax error at "<<@2.first_line<<":"<<@2.first_column<<":"<<@2.last_line<<":"<<@2.last_column<<std::endl;
					std::cerr<<"Error text: "<<error.what()<<std::endl;
				}
				if(!isError) std::cout<<var;
			}
	| VAR_NAME vars '<''<' VAR_NAME
						{
						vm.pushVarToInit(*$1);
						try
						{
							vm.flushAssign(vm.getVar(*$5).value);
						}
						catch(std::invalid_argument error)
						{
							if(vm.getErrCode()==Err::typeMisMatch || vm.getErrCode()==Err::undefined)
							{
								std::cerr<<"Syntax error at "<<@5.first_line<<":"<<@5.first_column<<":"<<@5.last_line<<":"<<@5.last_column<<std::endl;
							}
							else if(vm.getErrCode()==Err::redefinition)
							{
								std::cerr<<"Syntax error at "<<@2.first_line<<":"<<@2.first_column<<":"<<@2.last_line<<":"<<@2.last_column<<std::endl;
							}
							std::cerr<<"Error text: "<<error.what()<<std::endl;
							
						}
						bison_logger<<"All vars from init queue were intialized"<<std::endl;
							
						}
	| VAR_NAME vars '<''<' LITERAL
						{
						vm.pushVarToInit(*$1);
						try
						{
							vm.flushAssign($5);
						}
						catch(std::invalid_argument error)
						{
							if(vm.getErrCode()==Err::typeMisMatch || vm.getErrCode()==Err::undefined)
							{
								std::cerr<<"Syntax error at "<<@5.first_line<<":"<<@5.first_column<<":"<<@5.last_line<<":"<<@5.last_column<<std::endl;
							}
							else if(vm.getErrCode()==Err::redefinition)
							{
								std::cerr<<"Syntax error at "<<@2.first_line<<":"<<@2.first_column<<":"<<@2.last_line<<":"<<@2.last_column<<std::endl;
							}
							std::cerr<<"Error text: "<<error.what()<<std::endl;
							
						}
						bison_logger<<"All vars from init queue were intialized"<<std::endl;
							
						}
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



