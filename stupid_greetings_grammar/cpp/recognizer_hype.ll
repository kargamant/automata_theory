%option c++

%{
#include "hype.tab.hh"
#include <iostream>
//# include "Interpreter.h"
%}

id [0-9]+
hello Hello

%{
	#define YY_USER_ACTION loc.columns(yyleng);
	%}

%option noyywrap

%%

%{
	yy:location& loc=intrpr.location;
	loc.step();
%}

{id} 	return yy::parser::make_ID(yytext, loc);
{hello} return yy::parser::make_HELLO(std::string(yytext), loc);

%%


