#include <string>
#include <iostream>
class Recognizer
{
	protected:
		char lastChar;
		std::string line;
	public:
		virtual bool checkString(std::string& str)=0;
		void run(std::istream& in=std::cin, std::ostream& out=std::cout, bool noOutput=false);
		char lastRead() {return lastChar;}
		virtual ~Recognizer()=default;
};
