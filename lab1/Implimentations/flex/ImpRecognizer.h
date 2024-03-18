#include <Recognizer.h>
#include <string>
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

//private inheritance => it's no longer possible to create a pointer pointing to derived class

namespace Flex
{
	class ImpRecognizer : public Recognizer, private yyFlexLexer
	{
		public:
			bool checkString(const std::string& str) override;
	};
}
