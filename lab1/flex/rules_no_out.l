%{
#include <stdio.h>
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

{FOR}" "+{ID}" "+{IN}" "+{OBRACKET}" "*(({ID}|{STRING}|{DIGIT}+)" "+)+{CBRACKET}	{}
{FOR}" "+{ID}" "+{IN}" "+{OBRACKET}" "*(({ID}|{STRING}|{DIGIT}+)(" "+|{CBRACKET}))+	{}
.*	{}

%%
int main(int argc, char* argv[])
{
	const char* filename;
	if(argc!=1)
	{
		filename=argv[1];
		yyin=fopen(filename, "r");
	}
	yylex();
	fclose(yyin);
	return 0;
}
