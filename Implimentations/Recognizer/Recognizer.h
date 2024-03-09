#include <string>
class Recognizer
{
	public:
		virtual bool checkString(std::string& str)=0;
		virtual void run(std::istream& in, std::ostream& out)=0;

};
