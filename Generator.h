
class Generator
{
	private:
		std::string lastGenerated;
		std::string genNum(int length=1);
		char genChar(bool lowerCase=true);
		char genBadChar();
		int genChoice(int options=2);
		std::string genId(int length);
		std::string genStringLiteral(int length, bool doubleQoutes=false);
		std::string genSpaces(int length);
	public:
		std::string genCorrectString(int varLength, int maxSpacesLength, int words);
};
