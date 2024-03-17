#include <Recognizer.h>
#include <string>
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

//private inheritance => it's no longer possible to create a pointer pointing to derived class
class ImpRecognizer : public Recognizer, private yyFlexLexer
{
	public:
		bool checkString(std::string& str) override;
};
