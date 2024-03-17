#include <Recognizer.h>
#include <regex>

class ImpRecognizer : public Recognizer
{
	private:
		static const std::regex re;
	public:
		bool checkString(const std::string& str) override;
};
