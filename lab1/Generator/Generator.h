#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <random>

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
		//static int genFromTo(int a, int b);

		std::mt19937 engine;
	public:
		Generator(int varLength, int maxSpacesLength, int words) : varLength(varLength), maxSpacesLength(maxSpacesLength), words(words)
		{

			std::random_device rd;
			engine.seed(rd());
		}
		std::string genCorrectString();
		std::string genIncorrectString(const std::vector<std::string>& cases);
		int genChoice(int options=2);
};
