%require "3.2"

%token <str> VAR_NAME
%token <num> LITERAL
%token <var_type> VAR_TYPE

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
						vm.flushInit($1, $6);
						bison_logger<<"All vars from init queue were intialized"<<std::endl;
						}
	| '@' VAR_NAME
			{
				Var var=vm.getVar(*$2);
				std::cout<<var;
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
