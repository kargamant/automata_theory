#include "RegexRecognizer.h"


bool RegexRecognizer::checkString(std::string& str)
{
	str.pop_back();
	bool res=std::regex_match(str, re);
	str+=")";
	return res;
}


