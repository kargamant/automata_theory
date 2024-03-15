#include "FlexRecognizer.h"
#include <iostream>
#include <sstream>

bool FlexRecognizer::checkString(std::string& str)
{
	std::stringstream st{str};
	switch_streams(&st, &std::cout);
	return yylex();
}

