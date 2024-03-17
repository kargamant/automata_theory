#include "ImpRecognizer.h"

const std::regex ImpRecognizer::re=std::regex("for\\s+([a-zA-Z][\\w]+|[a-zA-Z])\\s+in\\s+\\(\\s*(((([a-zA-Z][\\w]+|[a-zA-Z])|'([^']+|)'|\"([^\"]+|)\"|[0-9]+)\\s+(([a-zA-Z][\\w]+|[a-zA-Z])|'([^']+|)'|\"([^\"]+|)\"|[0-9]+|\\s*)*)|(([a-zA-Z][\\w]+|[a-zA-Z])|'([^']+|)'|\"([^\"]+|)\"|[0-9]+))\\)");
bool ImpRecognizer::checkString(std::string& str)
{
	str.pop_back();
	bool res=std::regex_match(str, re);
	str+="\n";
	return res;
}


