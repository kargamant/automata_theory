#define CATCH_CONFIG_MAIN
#include "../../Catch2/catch.hpp"
#include "../bison/bis.tab.h"
//#include "../compile_vars.h"
#include <sstream>

extern FILE* yyin;
extern VarMap* vm;
extern std::stack<VarMap*> program_stack;
extern std::vector<Error> err_vec;
extern std::unordered_map<std::string, Ast*> declared_funcs;
extern Map labirint;


int parseStr(const std::string& str, const std::string& fname="buffer.boba");
void loadStr(const std::string& str, const std::string& fname="buffer.boba");
int parseFile(const std::string& fname="buffer.boba");
void clearBuffer(const std::string& fname="buffer.boba");
void cleanProgStack(std::stack<VarMap*>& prog_stack=program_stack);
void cleanErrorVec(std::vector<Error>& errors=err_vec);
void cleanDeclaredFuncs(std::unordered_map<std::string, Ast*>& funcs=declared_funcs);
void cleanCompileVars(std::vector<Error>& errors=err_vec, std::stack<VarMap*>& prog_stack=program_stack, std::unordered_map<std::string, Ast*>& funcs=declared_funcs);

int parseStr(const std::string& str, const std::string& fname)
{
	//clear(fname);
	std::fstream buffer{fname};
	buffer<<str;
	buffer.close();
	yyin=fopen(fname.c_str(), "r");
	int res=yyparse();
	fclose(yyin);
	clearBuffer(fname);
	return res;
	
}

void loadStr(const std::string& str, const std::string& fname)
{
	std::fstream buffer{fname, std::ios::app};
	buffer<<str;
	buffer.close();
}

int parseFile(const std::string& fname)
{
	yyin=fopen(fname.c_str(), "r");
	int res=yyparse();
	fclose(yyin);
	clearBuffer(fname);
	return res;
}

void clearBuffer(const std::string& fname)
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

void cleanErrorVec(std::vector<Error>& errors)
{
	errors.clear();
}

void cleanDeclaredFuncs(std::unordered_map<std::string, Ast*>& funcs)
{
	for(auto& f: funcs)
	{
		delete f.second;
	}
	funcs.clear();
}

void cleanCompileVars(std::vector<Error>& errors, std::stack<VarMap*>& prog_stack, std::unordered_map<std::string, Ast*>& funcs)
{
	cleanErrorVec(errors);
	cleanProgStack(prog_stack);
	cleanDeclaredFuncs(funcs);
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
		REQUIRE(err_vec.back().error_code==Err::typeMisMatch);
		

		parseStr("tiny c<<-1,.");
		REQUIRE(!vm->checkIfDefined("c"));
		REQUIRE(err_vec.back().error_code==Err::typeMisMatch);
		
		
		parseStr("tiny c<<1,.");
		REQUIRE(vm->checkIfDefined("c"));
		REQUIRE(vm->getVar("c")->value==1);

		parseStr("normal g<<1024,.");
		REQUIRE(!vm->checkIfDefined("g"));
		REQUIRE(err_vec.back().error_code==Err::typeMisMatch);

		parseStr("normal mm<<-513,.");
		REQUIRE(!vm->checkIfDefined("mm"));
		REQUIRE(err_vec.back().error_code==Err::typeMisMatch);

		parseStr("normal mm<<-512,.");
		REQUIRE(vm->checkIfDefined("mm"));
		REQUIRE(vm->getVar("mm")->value==-512);

		parseStr("normal mm<<3,.");
		REQUIRE(err_vec.back().error_code==Err::redefinition);
		REQUIRE(vm->checkIfDefined("mm"));
		REQUIRE(vm->getVar("mm")->value==-512);
		
		cleanCompileVars();
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
		REQUIRE(err_vec.back().error_code==Err::typeMisMatch);
		
		cleanCompileVars();
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

		cleanCompileVars();
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
		
		cleanCompileVars();
	}
}
TEST_CASE("one to one assignment")
{
	SECTION("number to variable assignment")
	{
		loadStr("small a<<7,");

		loadStr("a<<-3,.");
		parseFile();
		REQUIRE(vm->getVar("a")->value==-3);

		parseStr("a<<-16,.");	
		REQUIRE(vm->getVar("a")->value==-16);
		
		parseStr("a<<31,.");	
		REQUIRE(vm->getVar("a")->value==31);
		
		parseStr("a<<32,.");	
		REQUIRE(vm->getVar("a")->value==31);
		
		parseStr("a<<-32,.");	
		REQUIRE(vm->getVar("a")->value==-16);

		parseStr("-16>>a,.");	
		REQUIRE(vm->getVar("a")->value==-16);
		
		parseStr("31>>a,.");	
		REQUIRE(vm->getVar("a")->value==31);
		
		parseStr("32>>a,.");	
		REQUIRE(vm->getVar("a")->value==31);
		
		parseStr("-32>>a,.");	
		REQUIRE(vm->getVar("a")->value==-16);

		parseStr("a>>5,.");
		REQUIRE(err_vec.back().error_code==Err::invalidAssign);
		
		cleanCompileVars();
	}
	SECTION("variable to variable assignment")
	{
		loadStr("normal a<<33,");
		loadStr("small c<<-4,.");
		parseFile();

		parseStr("c>>a,.");
		REQUIRE(vm->getVar("a")->value==vm->getVar("c")->value);
		REQUIRE(vm->getVar("a")->value==-4);

		parseStr("88>>a,.");
		parseStr("c<<a,.");
		REQUIRE(vm->getVar("c")->value==(VarMap::size_table[VarType::small]-1));

		parseStr("a<<-88,.");
		parseStr("a>>c,.");
		REQUIRE(vm->getVar("c")->value==-(VarMap::size_table[VarType::small]/2));

		parseStr("a>>b,.");
		REQUIRE(err_vec.back().error_code==Err::undefined);
		
		parseStr("b>>a,.");
		REQUIRE(err_vec.back().error_code==Err::undefined);

		parseStr("a<<b,.");
		REQUIRE(err_vec.back().error_code==Err::undefined);

		parseStr("b<<a,.");
		REQUIRE(err_vec.back().error_code==Err::undefined);
		
		cleanCompileVars();
	}
}
TEST_CASE("chained assignment")
{
	SECTION("number to variables")
	{
		parseStr("normal a b c<<55,.");
		
		parseStr("a<<33>>b,.");
		REQUIRE(vm->getVar("a")->value==33);
		REQUIRE(vm->getVar("b")->value==33);

		parseStr("10000>>a>>b>>c,.");
		REQUIRE(vm->getVar("a")->value==1023);
		REQUIRE(vm->getVar("b")->value==1023);
		REQUIRE(vm->getVar("c")->value==1023);

		parseStr("a<<9,.");
		parseStr("a>>b<<44>>c,.");
		REQUIRE(vm->getVar("b")->value==44);
		REQUIRE(vm->getVar("c")->value==44);

		parseStr("a>>b>>33>>c,.");
		REQUIRE(err_vec.back().error_code==Err::invalidAssign);
		cleanErrorVec();

		parseStr("a>>45<<b,.");
		REQUIRE(err_vec.back().error_code==Err::invalidAssign);
		cleanErrorVec();

		parseStr("228<<c<<b<<a,.");
		REQUIRE(err_vec.back().error_code==Err::invalidAssign);
		cleanErrorVec();

		
		cleanCompileVars();
	}
	SECTION("variables to variables")
	{
		parseStr("normal a b c<<55,.");
		std::cout<<program_stack.top();

		parseStr("a<<18,.");
		parseStr("b<<33,.");
		//a=18, b=33, c=55
		parseStr("a>>b<<c,.");
		REQUIRE(vm->getVar("b")->value==vm->getVar("c")->value);
		
		parseStr("b<<22,.");
		parseStr("b>>a>>c,.");
		REQUIRE(vm->getVar("c")->value==22);
		REQUIRE(vm->getVar("a")->value==22);
		
		parseStr("c<<8,.");
		parseStr("a<<c>>b,.");
		REQUIRE(vm->getVar("b")->value==8);
		REQUIRE(vm->getVar("a")->value==8);

		parseStr("c<<9,.");
		parseStr("a<<-100,.");
		parseStr("b<<90,.");
		parseStr("c<<a<<b<<a,.");
		REQUIRE(vm->getVar("b")->value==-100);
		REQUIRE(vm->getVar("c")->value==-100);
		REQUIRE(vm->getVar("a")->value==-100);

		parseStr("c<<9,.");
		parseStr("a<<-100,.");
		parseStr("b<<90,.");
		parseStr("a>>b<<c<<b,.");
		REQUIRE(vm->getVar("a")->value==-100);
		REQUIRE(vm->getVar("b")->value==-100);
		REQUIRE(vm->getVar("c")->value==-100);

		parseStr("c<<9,.");
		parseStr("a<<-100,.");
		parseStr("b<<90,.");
		parseStr("a>>c<<c<<b>>c<<a,.");
		REQUIRE(vm->getVar("a")->value==-100);
		REQUIRE(vm->getVar("b")->value==90);
		REQUIRE(vm->getVar("c")->value==-100);
		

		cleanCompileVars();
	}
}
TEST_CASE("single arifmetic operations")
{
	SECTION("plus")
	{
		parseStr("normal a b c d<<3+5,.");
		REQUIRE(vm->getVar("a")->value==8);
		
		parseStr("a<<(b+c)+0,.");
		REQUIRE(vm->getVar("a")->value==(vm->getVar("b")->value+vm->getVar("c")->value));

		parseStr("(a+c+d)+(-3)>>b,.");
		REQUIRE(vm->getVar("b")->value==(vm->getVar("a")->value+vm->getVar("c")->value+vm->getVar("d")->value-3));

		parseStr("b>>(a+c),.");
		REQUIRE(err_vec.back().error_code==Err::invalidAssign);

		cleanCompileVars();
	}
	SECTION("minus")
	{
		parseStr("normal a b c d<<3-5,.");
		REQUIRE(vm->getVar("a")->value==-2);
		
		parseStr("a<<(b-c)+34,.");
		REQUIRE(vm->getVar("a")->value==(vm->getVar("b")->value-vm->getVar("c")->value+34));

		parseStr("(a+c-d)-10>>b,.");
		REQUIRE(vm->getVar("b")->value==(vm->getVar("a")->value+vm->getVar("c")->value-vm->getVar("d")->value-10));

		parseStr("(-9)+(-3-1)-13>>b,.");
		REQUIRE(vm->getVar("b")->value==-26);

		parseStr("b>>(a-c),.");
		REQUIRE(err_vec.back().error_code==Err::invalidAssign);

		cleanCompileVars();
	}
	SECTION("product")
	{
		parseStr("normal a b c d<<3*5*8,.");
		REQUIRE(vm->getVar("a")->value==120);
		
		parseStr("a<<b*c-d*c,.");
		REQUIRE(vm->getVar("a")->value==(vm->getVar("b")->value*vm->getVar("c")->value-vm->getVar("d")->value*vm->getVar("c")->value));

		parseStr("d*10>>b,.");
		REQUIRE(vm->getVar("b")->value==1023);

		parseStr("b<<1,.");
		parseStr("a<<3,.");
		parseStr("c<<-2,.");
		parseStr("(a+b)*(-c)*(-1)>>d,.");
		REQUIRE(vm->getVar("d")->value==-8);

		cleanCompileVars();
	}
	SECTION("division")
	{
		parseStr("normal a b c d<<3*5/5,.");
		REQUIRE(vm->getVar("a")->value==3);
		
		parseStr("b<<b*2,.");
		parseStr("a*(b/c)>>d,.");
		REQUIRE(vm->getVar("d")->value==6);
		
		parseStr("a*b/2>>d,.");
		REQUIRE(vm->getVar("d")->value==9);

		parseStr("d<<b/0,.");
		REQUIRE(vm->getVar("d")->value==1023);

		parseStr("b<<2,.");
		parseStr("a<<6,.");
		parseStr("d<<12,.");
		parseStr("c<<20,.");
		parseStr("b<<c/(d/(a/b)),.");
		REQUIRE(vm->getVar("b")->value==5);

		parseStr("b<<c/d/a/b,.");
		REQUIRE(vm->getVar("b")->value==0);

		cleanCompileVars();
	}
}

