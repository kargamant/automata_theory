%{
#include "bis.tab.h"
%}


hello Hello
hi Hi
howdy Howdy
hw {hello}|{hi}|{howdy}
id [0-9]+
nickname [a-zA-Z]+

%option noyywrap

%%
{id} {return *yytext;}
{hw} {return *yytext;}
{nickname} {return *yytext;}

%%
void yyerror(const char *s) {
	 fprintf(stderr, "%s\n", s);
}


