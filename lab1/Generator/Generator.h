#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>

class Generator
{
	private:
		int varLength;
		int maxSpacesLength;
		int words;
		std::string genNum(int length=1);
		char genChar(bool lowerCase=true);
		char genBadChar();
		std::string genId(int length);
		std::string genStringLiteral(int length, bool doubleQoutes=false);
		std::string genSpaces(int length);
		std::string genAbsRandString(int length);
	public:
		Generator(int varLength, int maxSpacesLength, int words) : varLength(varLength), maxSpacesLength(maxSpacesLength), words(words)
		{
			std::srand(std::time(nullptr));
		}
		std::string genCorrectString();
		std::string genIncorrectString(std::vector<std::string>& cases);
		int genChoice(int options=2);
};
