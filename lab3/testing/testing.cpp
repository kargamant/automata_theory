#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../bison/bis.tab.h"
//#include "../compile_vars.h"
#include <sstream>

extern FILE* yyin;
extern VarMap* vm;
std::fstream buffer{"buffer.boba"};

TEST_CASE("definition")
{
	SECTION("single definition")
	{
		std::string exp="small a<<7,.";
		buffer<<exp;
		buffer.close();
		yyin=fopen("buffer.boba", "r");
		int ret = yyparse();
		REQUIRE(vm->checkIfDefined("a"));
		REQUIRE(vm->getVar("a")->value==7);
	}
}
