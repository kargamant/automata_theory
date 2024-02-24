%{
#include <stdio.h>
//for[\s]+([a-zA-Z][\w]+|[a-zA-Z])[\s]+in[\s]+\((?:[\w\s]+|\'([^\']+|)\'|\"([^\"]+|)\")+\)
%}

SYMB [a-zA-Z]
DIGIT [0-9]
FOR for
ID {SYMB}({SYMB}|{DIGIT})+
IN in
OBRACKET "("
STRING ("'".*"'")|("\"".*"\"")
CBRACKET ")"

%%

{FOR}" "+{ID}" "+{IN}" "+{OBRACKET}({ID}|{STRING}|" ")+{CBRACKET}	{return 1;}
.*	{return 0;}

%%
int main()
{
	if(yylex()) printf("correct\n");
	else printf("incorrect\n");
	return 0;
}
