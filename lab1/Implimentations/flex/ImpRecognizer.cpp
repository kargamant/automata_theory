#include "ImpRecognizer.h"
#include <iostream>
#include <sstream>

namespace Flex
{
	bool ImpRecognizer::checkString(const std::string& str)
	{
		std::stringstream st{str};
		switch_streams(&st, &std::cout);
		return yylex();
	}
}


