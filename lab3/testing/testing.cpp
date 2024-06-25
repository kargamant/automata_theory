#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../bison/bis.tab.h"
//#include "../compile_vars.h"
#include <sstream>

extern FILE* yyin;
extern VarMap* vm;
extern std::stack<VarMap*> program_stack;
extern std::unordered_map<std::string, Ast*> declared_funcs;
extern Map labirint;


int parseStr(const std::string& str, const std::string& fname="buffer.boba");
void clear(const std::string& fname="buffer.boba");
void cleanProgStack(std::stack<VarMap*>& prog_stack);

int parseStr(const std::string& str, const std::string& fname)
{
	//clear(fname);
	std::fstream buffer{fname};
	buffer<<str;
	buffer.close();
	yyin=fopen(fname.c_str(), "r");
	int res=yyparse();
	fclose(yyin);
	clear(fname);
	return res;
	
}

void clear(const std::string& fname)
{
	FILE* f=fopen(fname.c_str(), "w");
	fclose(f);
}

void cleanProgStack(std::stack<VarMap*>& prog_stack)
{
	while(!prog_stack.empty())
	{
		prog_stack.top()->clear();
		program_stack.pop();
	}

}

TEST_CASE("definition")
{
	SECTION("single variable definition")
	{
		parseStr("small a<<7,.");
		REQUIRE(vm->checkIfDefined("a"));
		REQUIRE(vm->getVar("a")->value==7);


		parseStr("normal b<<-7,.");
		REQUIRE(vm->checkIfDefined("b"));
		REQUIRE(vm->getVar("b")->value==-7);
		
	
		parseStr("tiny c<<5,.");
		REQUIRE(!vm->checkIfDefined("c"));
		

		parseStr("tiny c<<-1,.");
		REQUIRE(!vm->checkIfDefined("c"));
		
		
		parseStr("tiny c<<1,.");
		REQUIRE(vm->checkIfDefined("c"));
		REQUIRE(vm->getVar("c")->value==1);

		parseStr("normal g<<1024,.");
		REQUIRE(!vm->checkIfDefined("g"));

		parseStr("normal mm<<-513,.");
		REQUIRE(!vm->checkIfDefined("mm"));

		parseStr("normal mm<<-512,.");
		REQUIRE(vm->checkIfDefined("mm"));
		REQUIRE(vm->getVar("mm")->value==-512);
		
		cleanProgStack(program_stack);
	}
	SECTION("multiple variable definition")
	{
		parseStr("small a b c<<-3,.");
		REQUIRE(vm->checkIfDefined("a"));
		REQUIRE(vm->checkIfDefined("b"));
		REQUIRE(vm->checkIfDefined("c"));
		REQUIRE(vm->getVar("a")->value==-3);
		REQUIRE(vm->getVar("b")->value==-3);
		REQUIRE(vm->getVar("c")->value==-3);

		parseStr("normal gg hh mm<<1024,.");
		REQUIRE(!vm->checkIfDefined("gg"));
		REQUIRE(!vm->checkIfDefined("hh"));
		REQUIRE(!vm->checkIfDefined("mm"));
		
		cleanProgStack(program_stack);
	}
	SECTION("single field definition")
	{
		parseStr("field tiny small ff<<1,.");
		REQUIRE(vm->checkIfDefined("ff"));
		REQUIRE(vm->getVar("ff")->isField);
		REQUIRE(dynamic_cast<Field*>(vm->getVar("ff"))->matr.size()==VarMap::size_table[VarType::small]*VarMap::size_table[VarType::small]);
		for(auto& v: dynamic_cast<Field*>(vm->getVar("ff"))->matr)
		{
			REQUIRE(v->type==VarType::tiny);
			REQUIRE(v->value==1);
		}

		for(int i=0; i<VarMap::size_table[VarType::small]; i++)
		{
			for(int j=0; j<VarMap::size_table[VarType::small]; j++)
			{
				REQUIRE(dynamic_cast<Field*>(vm->getVar("ff"))->getVar(i, j)->value==1);
			}
		}

		parseStr("field small normal gg<<-17,.");
		REQUIRE(!vm->checkIfDefined("gg"));

		cleanProgStack(program_stack);
	}
	SECTION("multiple field definition")
	{
		parseStr("field small normal gg hh ff<<15,.");
		REQUIRE(vm->checkIfDefined("gg"));
		REQUIRE(vm->checkIfDefined("hh"));
		REQUIRE(vm->checkIfDefined("ff"));
		REQUIRE(vm->getVar("ff")->isField);
		REQUIRE(vm->getVar("gg")->isField);
		REQUIRE(vm->getVar("hh")->isField);
		REQUIRE(dynamic_cast<Field*>(vm->getVar("ff"))->matr.size()==VarMap::size_table[VarType::normal]*VarMap::size_table[VarType::normal]);
		REQUIRE(dynamic_cast<Field*>(vm->getVar("gg"))->matr.size()==VarMap::size_table[VarType::normal]*VarMap::size_table[VarType::normal]);
		REQUIRE(dynamic_cast<Field*>(vm->getVar("hh"))->matr.size()==VarMap::size_table[VarType::normal]*VarMap::size_table[VarType::normal]);
		
		for(auto& v: dynamic_cast<Field*>(vm->getVar("ff"))->matr)
		{
			REQUIRE(v->type==VarType::small);
			REQUIRE(v->value==15);
		}

		for(int i=0; i<VarMap::size_table[VarType::normal]; i++)
		{
			for(int j=0; j<VarMap::size_table[VarType::normal]; j++)
			{
				REQUIRE(dynamic_cast<Field*>(vm->getVar("ff"))->getVar(i, j)->value==15);
			}
		}
		
		for(auto& v: dynamic_cast<Field*>(vm->getVar("gg"))->matr)
		{
			REQUIRE(v->type==VarType::small);
			REQUIRE(v->value==15);
		}

		for(int i=0; i<VarMap::size_table[VarType::normal]; i++)
		{
			for(int j=0; j<VarMap::size_table[VarType::normal]; j++)
			{
				REQUIRE(dynamic_cast<Field*>(vm->getVar("gg"))->getVar(i, j)->value==15);
			}
		}
		
		for(auto& v: dynamic_cast<Field*>(vm->getVar("hh"))->matr)
		{
			REQUIRE(v->type==VarType::small);
			REQUIRE(v->value==15);
		}

		for(int i=0; i<VarMap::size_table[VarType::normal]; i++)
		{
			for(int j=0; j<VarMap::size_table[VarType::normal]; j++)
			{
				REQUIRE(dynamic_cast<Field*>(vm->getVar("hh"))->getVar(i, j)->value==15);
			}
		}
		
		cleanProgStack(program_stack);
	}
}





