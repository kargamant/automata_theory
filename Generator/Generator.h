#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class Generator
{
	private:
		int varLength;
		int maxSpacesLength;
		int words;
		std::string lastGenerated;
		std::string genNum(int length=1);
		char genChar(bool lowerCase=true);
		char genBadChar();
		int genChoice(int options=2);
		std::string genId(int length);
		std::string genStringLiteral(int length, bool doubleQoutes=false);
		std::string genSpaces(int length);
		std::string genAbsRandString(int length);
	public:
		Generator(int varLength, int maxSpacesLength, int words) : varLength(varLength), maxSpacesLength(maxSpacesLength), words(words)
	{
	}
		std::string genCorrectString();
		std::string genIncorrectString(std::vector<std::string> cases);
};
