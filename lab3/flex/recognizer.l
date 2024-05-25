%{
#include "../bison/bis.tab.h"
#include <cstdlib>
#include <string>
#include "../Ast/Ast.h"
std::ofstream flex_logger("report_flex.txt");
%}

letter [a-zA-Z]
digit [0-9]
literal (-?[1-9][0-9]*|0)
var_name [a-zA-Z]([a-zA-Z]|[0-9])*
var_type tiny|small|normal|big
array field
left_assign <<
right_assign >>
more_equal =>
less_equal <=
until until
check check
do do


%option noyywrap

%%

{var_type}	{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);
			
			flex_logger<<yytext<<std::endl;
			flex_logger<<"var_type parsed"<<std::endl;
			yylval.var_type=typeByName(std::string(yytext));
			return VAR_TYPE;
		}
{array}		{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"array_type parsed"<<std::endl;
			return ARRAY;

		}
{until}		{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"until parsed"<<std::endl;
			return UNTIL;
		}
{check}		{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"check parsed"<<std::endl;
			return CHECK;
		}
{do}		{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"do parsed"<<std::endl;
			return DO;
		}

{var_name}	{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"var_name parsed"<<std::endl;
			yylval.str=new std::string(yytext);
			//yylval.str=(char*)malloc(yyleng+1);
			//strcpy(yylval.str, yytext);
			return VAR_NAME;
		}
{left_assign}	{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"left_assign parsed"<<std::endl;
			return LEFT_ASSIGN;
		
		}
{right_assign}	{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"right_assign parsed"<<std::endl;
			return RIGHT_ASSIGN;
		
		}
{more_equal}	{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"more_equal parsed"<<std::endl;
			return MORE_EQUAL;
			
		}
{less_equal}	{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"less_equal parsed"<<std::endl;
			return LESS_EQUAL;
			
		}

">"|"<"|"("|")"|"/"|"*"|"-"|"+"|","|"."|"@"|"["|"]"|"$"		{
						yylloc.first_column=yylloc.last_column+1;
						yylloc.last_column+=strlen(yytext);

						flex_logger<<yytext<<std::endl;
						flex_logger<<*yytext<<" parsed"<<std::endl;
						return *yytext;	
						}

{literal} 	{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"literal parsed"<<std::endl;
			yylval.num=atoi(yytext);
			return LITERAL;
		}
"\n"		{
			yylloc.last_line=++yylloc.first_line;
			yylloc.last_column=yylloc.first_column=0;
		}

%%


