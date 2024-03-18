#include "ImpRecognizer.h"

namespace Regex
{
	const std::regex ImpRecognizer::re=std::regex("for\\s+([a-zA-Z][\\w]+|[a-zA-Z])\\s+in\\s+\\(\\s*(((([a-zA-Z][\\w]+|[a-zA-Z])|'([^']+|)'|\"([^\"]+|)\"|[0-9]+)\\s+(([a-zA-Z][\\w]+|[a-zA-Z])|'([^']+|)'|\"([^\"]+|)\"|[0-9]+|\\s*)*)|(([a-zA-Z][\\w]+|[a-zA-Z])|'([^']+|)'|\"([^\"]+|)\"|[0-9]+))\\)(\\n)*");

	bool ImpRecognizer::checkString(const std::string& str)
	{
		bool res=std::regex_match(str, re);
		return res;
	}
}

