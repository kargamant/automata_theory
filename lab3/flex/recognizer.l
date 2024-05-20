%{
#include "../bison/bis.tab.h"
#include <cstdlib>
#include <string>
%}

letter [a-zA-Z]
digit [0-9]
literal (-?[1-9][0-9]*|0)
var_name [a-zA-Z]([a-zA-Z]|[0-9])*
var_type tiny|small|normal|big


%option noyywrap

%%

{var_type}	{
			std::cout<<"var_type parsed"<<std::endl;
			yylval.var_type=typeByName(std::string(yytext));
			return VAR_TYPE;
		}

{var_name}	{
			std::cout<<"var_name parsed"<<std::endl;
			yylval.str=new std::string(yytext);
			//yylval.str=(char*)malloc(yyleng+1);
			//strcpy(yylval.str, yytext);
			return VAR_NAME;
		}

"<"|","|"."|"@"		{
			std::cout<<*yytext<<" parsed"<<std::endl;
			return *yytext;	
		}

{literal} 	{
			std::cout<<"literal parsed"<<std::endl;
			yylval.num=atoi(yytext);
			return LITERAL;
		}

%%


