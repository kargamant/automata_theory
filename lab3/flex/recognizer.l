%{
#include "../bison/bis.tab.h"
#include <cstdlib>
#include <string>
%}

letter [a-zA-Z]
digit [0-9]
literal (-?[1-9]+|0)
var_name [a-zA-Z]([a-zA-Z]|[0-9])+


%option noyywrap

%%

{var_name}	{
			yylval.str=new std::string(yytext);
			std::cout<<"jopa"<<std::endl;
			//yylval.str=(char*)malloc(yyleng+1);
			//strcpy(yylval.str, yytext);
			return VAR_NAME;
		}
{literal} 	{
			yylval.num=atoi(yytext);
			return LITERAL;
		}

%%


