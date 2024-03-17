%option c++
%{
#include <iostream>
#include <fstream>
#include "ImpRecognizer.h"
//for[\s]+([a-zA-Z][\w]+|[a-zA-Z])[\s]+in[\s]+\((?:[\w\s]+|\'([^\']+|)\'|\"([^\"]+|)\")+\)
//{FOR}" "+{ID}" "+{IN}" "+{OBRACKET}(({ID}|{STRING}|{DIGIT}+)+|" "("?!"{CBRACKET})){CBRACKET}	{printf("line \"%s\" is correct\n", yytext);}
//SPACE_CONDITION (?(?={CBRACKET})|" "*|" "+)
//Cases to cover:
//for i in (abc 'popop'  123 )
//for i in (abc 'popop'  123)
%}

SYMB [a-zA-Z]
DIGIT [0-9]
FOR for
ID {SYMB}({SYMB}|{DIGIT})*
IN in
OBRACKET "("
STRING ("'"[^"'"]+"'")|("\""[^"\""]+"\"")
CBRACKET ")"

%option noyywrap

%%

{FOR}[" "\t]+{ID}[" "\t]+{IN}[" "\t]+{OBRACKET}[" "\t]*(({ID}|{STRING}|{DIGIT}+)[" "\t]+)+{CBRACKET}	{return 1; }
{FOR}[" "\t]+{ID}[" "\t]+{IN}[" "\t]+{OBRACKET}[" "\t]*(({ID}|{STRING}|{DIGIT}+)([" "\t]+|{CBRACKET}))+	{return 1; }
.*	{return 0; }

%%
/*int main(int argc, char* argv[])
{
	ImpRecognizer rec;
	if(argc==2)
	{
		if(std::string(argv[1])=="--no-output") 
		{
			rec.run(std::cin, std::cout, true);
		}
		else
		{
			std::fstream fs{argv[1], std::ios::out};
			fs.close();
			fs.open(argv[1]);
			rec.run(std::cin, fs);
		}
	}
	else rec.run();
	return 0;
}*/
