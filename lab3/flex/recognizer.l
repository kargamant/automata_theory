%{
#include "../bison/bis.tab.h"
#include <cstdlib>
#include <string>
std::ofstream flex_logger("report_flex.txt");
%}

letter [a-zA-Z]
digit [0-9]
literal (-?[1-9][0-9]*|0)
var_name [a-zA-Z]([a-zA-Z]|[0-9])*
var_type tiny|small|normal|big
array field


%option noyywrap

%%

{var_type}	{
			flex_logger<<yytext<<std::endl;
			flex_logger<<"var_type parsed"<<std::endl;
			yylval.var_type=typeByName(std::string(yytext));
			return VAR_TYPE;
		}
{array}		{
			flex_logger<<yytext<<std::endl;
			flex_logger<<"array_type parsed"<<std::endl;
			return ARRAY;

		}

{var_name}	{
			flex_logger<<yytext<<std::endl;
			flex_logger<<"var_name parsed"<<std::endl;
			yylval.str=new std::string(yytext);
			//yylval.str=(char*)malloc(yyleng+1);
			//strcpy(yylval.str, yytext);
			return VAR_NAME;
		}

"<"|","|"."|"@"|"["|"]"		{
			flex_logger<<yytext<<std::endl;
			flex_logger<<*yytext<<" parsed"<<std::endl;
			return *yytext;	
		}

{literal} 	{
			flex_logger<<yytext<<std::endl;
			flex_logger<<"literal parsed"<<std::endl;
			yylval.num=atoi(yytext);
			return LITERAL;
		}

%%


