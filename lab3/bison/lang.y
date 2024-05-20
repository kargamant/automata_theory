%require "3.2"

%token <str> VAR_NAME
%token <num> LITERAL

%code requires {
	#include <iostream>
	#include <string>
	#include <unordered_map>
}
%{
	int yylex(void);
	void yyerror(const char *s);
	
%}

%union
{
	std::string* str;
	int num;
}


%%
simple_statement:
	VAR_NAME LITERAL {
					std::cout<<"tiny "<<*$1<<" was assigned "<<$2<<std::endl;
					//printf("tiny %s was assigned %d\n", $1, $2);
					}
	| '.' {
		std::cout<<"the end"<<std::endl;
		//printf("the end\n");
		}

%%


void yyerror(const char *s) {
	 fprintf(stderr, "%s\n", s);
}
