#include "../../Recognizer/Recognizer.h"
#include <string>
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

class FlexRecognizer : public Recognizer, public yyFlexLexer
{
	public:
		bool checkString(std::string& str) override;
};
