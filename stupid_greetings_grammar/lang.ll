%{
#include "bis.tab.h"
#include <stdlib.h>
%}


hw Hello|Hi|Howdy
id [0-9]+
nickname [a-zA-Z]+

%option noyywrap

%%
{id} {
	yylval.id_type = atoi(yytext);  
	//printf("id parsed.\n"); 
	return ID;
     }
{hw} {
	//printf("h-word parced.\n");
	return H_WORD;
     }
{nickname} {
	yylval.name_type = malloc(yyleng + 1);  
	strcpy(yylval.name_type, yytext);
	//printf("nickname parced.\n"); 
	return NAME;
	   }
"." {
	//printf("dot parced.\n"); 
	return DOT;

	}

%%
void yyerror(const char *s) {
	 fprintf(stderr, "%s\n", s);
}


