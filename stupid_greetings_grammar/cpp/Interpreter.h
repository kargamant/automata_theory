#include "hype.tab.hh"
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

# define YY_DECL \
	  yy::parser::symbol_type yylex (Interpreter& intrpr)
// ... and declare it for the parser's sake.
YY_DECL;

class Interpreter : private yyFlexLexer
{
	public:
		Interpreter();
		std::string file;

		void scan();
		yy::parser::symbol_type parse(const std::string& str);
};
