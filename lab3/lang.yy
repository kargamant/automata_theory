%require "3.2"

%{
	#include <stdio.h>
	int yylex(void);
%}

%union
{
	int id_type;
	char* name_type;
}

%token <id_type> ID
%token <name_type> NAME
%token <name_type> H_WORD

%%

greetings:
	H_WORD ID 	{
				printf("%d is greeted\n", yylval);
			}
	| H_WORD NAME 	{
				printf("%s is greeted\n", yylval);
			}
	;
%%

