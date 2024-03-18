#include <Recognizer.h>
#include <regex>

namespace Regex
{
	class ImpRecognizer : public Recognizer
	{
		private:
			static const std::regex re;
		public:
			bool checkString(const std::string& str) override;
	};
}
