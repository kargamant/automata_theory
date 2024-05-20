%require "3.2"

%token <str> VAR_NAME
%token <num> LITERAL
%token <var_type> VAR_TYPE

%code requires {
	#include <iostream>
	#include <string>
	#include "../VarMap/VarMap.h"
}
%{
	#include "../VarMap/VarMap.h"
	int yylex(void);
	void yyerror(const char *s);
	VarMap vm;	
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
	VAR_TYPE VAR_NAME '<''<' LITERAL {
					//std::string var_name=std::string(*$2);
					vm.addVar(Var($1, *$2, $5));
					std::cout<<nameByType($1)<<" "<<*$2<<" was assigned "<<$5<<std::endl;
					}
	| '@' VAR_NAME
			{
				Var var=vm.getVar(*$2);
				std::cout<<var;
			}
%%


void yyerror(const char *s) {
	 fprintf(stderr, "%s\n", s);
}
