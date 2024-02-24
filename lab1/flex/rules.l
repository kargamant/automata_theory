%{
#include <stdio.h>
//for[\s]+([a-zA-Z][\w]+|[a-zA-Z])[\s]+in[\s]+\((?:[\w\s]+|\'([^\']+|)\'|\"([^\"]+|)\")+\)
%}

SYMB [a-zA-Z]
DIGIT [0-9]
FOR for
ID {SYMB}({SYMB}|{DIGIT})*
IN in
OBRACKET "("
STRING ("'".*"'")|("\"".*"\"")
CBRACKET ")"

%%

{FOR}" "+{ID}" "+{IN}" "+{OBRACKET}({ID}" "+|{STRING}" "+|{DIGIT}+" "+)+{CBRACKET}	{printf("line \"%s\" is correct\n", yytext);}
.*	{printf("line \"%s\" is incorrect\n", yytext);}

%%
int main(int argc, char* argv[])
{
	const char* filename;
	if(argc!=1)
	{
		filename=argv[1];
	}
	yyin=fopen(filename, "r");
	yylex();
	fclose(yyin);
	return 0;
}
