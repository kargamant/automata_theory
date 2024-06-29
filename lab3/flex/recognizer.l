%{
#include "../bison/bis.tab.h"
#include <cstdlib>
#include <string>
#include "../Ast/Ast.h"
std::ofstream flex_logger("report_flex.txt");
%}

letter [a-zA-Z]
digit [0-9]
literal ([1-9][0-9]*|0)
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
begin begin
end end
return return
go go
rl rl
rr rr
sonar sonar
compass compass


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
{go}		{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"go parsed"<<std::endl;
			return GO;
		}
{rl}		{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"rl parsed"<<std::endl;
			return RL;
		}
{rr}		{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"rr parsed"<<std::endl;
			return RR;
		}
{sonar}		{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"sonar parsed"<<std::endl;
			return SONAR;
		}
{compass}		{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"compass parsed"<<std::endl;
			return COMPASS;
		}
{return}	{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"return parsed"<<std::endl;
			return RETURN;
		}
{begin}		{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"begin parsed"<<std::endl;
			return BEGIN_FUNC;
		}
{end}		{
			yylloc.first_column=yylloc.last_column+1;
			yylloc.last_column+=strlen(yytext);

			flex_logger<<yytext<<std::endl;
			flex_logger<<"end parsed"<<std::endl;
			return END_FUNC;
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


