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
%token <name_type> DOT
%token <name_type> H_WORD

%%

greetings:
	H_WORD person greetings	{}
	| DOT {
					printf("Okay. Goodbye.\n");
		}

	;
person:
	ID 	{
			printf("%d is greeted\n", yylval);
			fflush(stdin);			
		}
	| NAME	{
			printf("%s is greeted\n", yylval);
			if(yylval.name_type!=NULL)
			{
				free(yylval.name_type);
				yylval.name_type=NULL;
			}
			fflush(stdin);
			
		}
	;
%%

