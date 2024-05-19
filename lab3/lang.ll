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
	printf("id parsed.\n"); 
	return ID;
     }
{hw} {
	if(yylval.name_type!=NULL) free(yylval.name_type);
	yylval.name_type = malloc(yyleng + 1);  
	memcpy(yylval.name_type, yytext, yyleng + 1);
	printf("h-word parced.\n");
	return H_WORD;
     }
{nickname} {
	if(yylval.name_type!=NULL) free(yylval.name_type);
	yylval.name_type = malloc(yyleng + 1);  
	memcpy(yylval.name_type, yytext, yyleng + 1);
	printf("nickname parced.\n"); 
	return NAME;
	   }

%%
void yyerror(const char *s) {
	 fprintf(stderr, "%s\n", s);
}


