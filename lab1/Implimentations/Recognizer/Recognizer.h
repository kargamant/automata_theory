#include <string>
#include <iostream>
class Recognizer
{
	public:
		virtual bool checkString(const std::string& str)=0;
};
