#include <Recognizer.h>
#include <regex>

class ImpRecognizer : public Recognizer
{
	private:
		static const std::regex re;
		//std::regex re;
	public:
		//RegexRecognizer() : re(str, std::regex_constants::optimize) {}
		bool checkString(std::string& str) override;
};
