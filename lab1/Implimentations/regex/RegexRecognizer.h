#include <Recognizer.h>
#include <regex>

class RegexRecognizer : public Recognizer
{
	private:
		std::regex re;
	public:
		RegexRecognizer(std::string& str) : re(str, std::regex_constants::optimize) {}
		bool checkString(std::string& str) override;
};
