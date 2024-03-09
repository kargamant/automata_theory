#include <string>
class Recognizer
{
	protected:
		char lastChar;
		std::string line;
	public:
		virtual bool checkString(std::string& str)=0;
		void run(std::istream& in, std::ostream& out);
		char lastRead() {return lastChar;}

};
