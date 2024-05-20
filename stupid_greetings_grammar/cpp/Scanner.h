#include "Interpreter.h"

class Scanner : public yyFlexLexer {
	public:
		Scanner(Interpreter &driver) : m_driver(driver) {}
		virtual ~Scanner() {}
		virtual EzAquarii::Parser::symbol_type get_next_token();
	private:
		Interpreter &m_driver;
};
