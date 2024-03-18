#include <string>
#include <iostream>
#pragma once
class Recognizer
{
	public:
		virtual bool checkString(const std::string& str)=0;
};
