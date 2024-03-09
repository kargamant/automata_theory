%option c++
%{
#include <iostream>
#include "FlexRecognizer.h"
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

{FOR}" "+{ID}" "+{IN}" "+{OBRACKET}" "*(({ID}|{STRING}|{DIGIT}+)" "+)+{CBRACKET}	{return 1; }
{FOR}" "+{ID}" "+{IN}" "+{OBRACKET}" "*(({ID}|{STRING}|{DIGIT}+)(" "+|{CBRACKET}))+	{return 1; }
.*	{return 0; }

%%
int main(int argc, char* argv[])
{
	/*const char* filename;
	if(argc!=1)
	{
		filename=argv[1];
		yyFlexLexer::yyout=fopen(filename, "w");
	}*/
	FlexRecognizer rec;
	std::string line="for i in (0)";	
	int result=rec.checkString(line);
	std::cout<<"res: "<<result<<std::endl;
	//int result=yylex();
	//if(result) fprintf(yyout, "line \"%s\" is correct\n", yytext);
	//else fprintf(yyout, "line \"%s\" is incorrect\n", yytext);
	/*yyin=stdin;
	do 
	{
		int result=yylex();
		if(result) fprintf(yyout, "line \"%s\" is correct\n", yytext);
		else fprintf(yyout, "line \"%s\" is incorrect\n", yytext);
		//clearerr(yyin);
	}while(*yytext!='\0');*/
	//fclose(yyout);
	return 0;
}
