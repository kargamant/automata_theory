#include "Interpreter.h"


void Interpreter::scan()
{
	yyin=stdin;
}

yy::parser::symbol_type Intepreter::parse (const std::string &f)
{
	file=f;
	location.initialize(&file);
	scan();
	yy::parser parse (*this);
	yy::parser::symbol_type res = parse ();
	return res;
}
/*int Interpreter::parse(const std::string& str)
{
	std::stringstream st{str};
	switch_streams(&st, &std::cout);
	return yylex();
}*/
