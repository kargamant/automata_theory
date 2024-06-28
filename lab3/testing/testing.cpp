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

		parseStr("ff[7 7]<<0,.");
		REQUIRE(dynamic_cast<Field*>(vm->getVar("ff"))->getVar(7, 7)->value==0);
		
		parseStr("ff[32 32]<<0,.");
		REQUIRE(err_vec.back().error_code==Err::outOfRange);

	//	parseStr("field small normal gg<<-17,.");
	//	REQUIRE(!vm->checkIfDefined("gg"));

	//	parseStr("gg[0 0]<<1,.");
	//	REQUIRE(err_vec.back().error_code==Err::undefined);

		parseStr("normal kk<<55,.");
		parseStr("kk[1 1]<<7,.");
		REQUIRE(err_vec.back().error_code==Err::typeMisMatch);

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
TEST_CASE("arifmetic operations")
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

TEST_CASE("logic operations")
{
	SECTION("numbers")
	{
		parseStr("normal a<<33,.");

		parseStr("a<<1<5,.");
		REQUIRE(vm->getVar("a")->value==1);

		parseStr("a<<1>5,.");
		REQUIRE(vm->getVar("a")->value==0);

		parseStr("a<<1=>5,.");
		REQUIRE(vm->getVar("a")->value==0);
		
		parseStr("a<<1<=5,.");
		REQUIRE(vm->getVar("a")->value==1);

		parseStr("a<<-1<=5<=0,.");
		REQUIRE(vm->getVar("a")->value==0);
		
		parseStr("a<<-1<=(5<=0),.");
		REQUIRE(vm->getVar("a")->value==1);

		parseStr("normal d c<<4,.");
		parseStr("a<<d<=c,.");
		REQUIRE(vm->getVar("a")->value==1);
		
		parseStr("a<<d<c,.");
		REQUIRE(vm->getVar("a")->value==0);

		parseStr("c<<(c+1),.");
		parseStr("a<<d<c,.");
		REQUIRE(vm->getVar("a")->value==1);

		parseStr("a<<d>c<a,.");
		REQUIRE(vm->getVar("a")->value==1);

		parseStr("tiny result<<0,.");
		parseStr("a<<-9,.");
		parseStr("c<<5,.");
		parseStr("d<<1,.");
		parseStr("result<<(a<(d<=(c=>d)))<a,.");
		REQUIRE(vm->getVar("result")->value==0);
		
		parseStr("result<<a<(d<=(c=>d))<a,.");
		REQUIRE(vm->getVar("result")->value==1);
		
		//testing priority
		parseStr("result<<1>2<=(-1),.");
		REQUIRE(vm->getVar("result")->value==1);

		cleanCompileVars();
	}
	SECTION("expressions")
	{
		parseStr("tiny result<<0,.");
		
		parseStr("result<<(1+1)=>1,.");
		REQUIRE(vm->getVar("result")->value==1);

		parseStr("result<<(5<(-30))=>(-1+1),.");
		REQUIRE(vm->getVar("result")->value==1);

		parseStr("result<<(((6+7)<(8*9))),.");
		REQUIRE(vm->getVar("result")->value==1);

		parseStr("normal a b c<<1023,.");
		parseStr("b<<130,.");
		parseStr("c<<-390,.");
		parseStr("result<<(a+c)*b=>(a*c+b)<b+a-c,.");
		REQUIRE(vm->getVar("result")->value==1);

		parseStr("normal kk<<7,.");
		parseStr("b<<49,.");
		parseStr("a<<343,.");
		parseStr("result<<a/b=>kk*7<=a*kk/b");
		REQUIRE(vm->getVar("result")->value==1);

		cleanCompileVars();
	}
}

TEST_CASE("chained assignment with logic and arifmetic expressions")
{
	SECTION("logic")
	{
		parseStr("normal a b c d<<12,.");
		parseStr("a<<3,.");
		parseStr("b<<-100,.");
		parseStr("c<<50,.");
		parseStr("d<<140,.");
	
		parseStr("a<c>>b<<a>c,.");
		REQUIRE(vm->getVar("b")->value==0);

		parseStr("b<<-100,.");
		parseStr("c<<a=>c>b>>d<<3*d<a,.");
		REQUIRE(vm->getVar("c")->value==1);
		REQUIRE(vm->getVar("d")->value==0);
		
		parseStr("c<<50,.");
		parseStr("d<<140,.");
		parseStr("a>>c<d<<b,.");
		REQUIRE(err_vec.back().error_code==Err::invalidAssign);

		//to be debugged
	//	parseStr("d>c<a>>c<<a>b<c=>d>>a,.");
	//	REQUIRE(vm->getVar("a")->value==0);
	//	REQUIRE(vm->getVar("c")->value==0);

		cleanCompileVars();
	}
	SECTION("arifmetic")
	{
		parseStr("normal a b c d<<12,.");
		parseStr("a<<3,.");
		parseStr("b<<-10,.");
		parseStr("c<<5,.");
		parseStr("d<<14,.");

		parseStr("(a+b)*c>>d<<d*a+b,.");
		REQUIRE(vm->getVar("d")->value==-115);

		parseStr("d<<14,.");
		parseStr("d<<b/(d/(a+4))+c>>a<<d/a,.");
		REQUIRE(vm->getVar("a")->value==(VarMap::size_table[VarType::normal]-1));
		REQUIRE(vm->getVar("d")->value==0);

		parseStr("a<<3,.");
		parseStr("d<<14,.");
		parseStr("(a+b-a*(d/c))>>c<<d*b>>a<<-c,.");
		REQUIRE(vm->getVar("a")->value==13);
		REQUIRE(vm->getVar("c")->value==-140);

		cleanCompileVars();
	}
}

TEST_CASE("check operator")
{
	SECTION("standard tests")
	{
		loadStr("small a<<3,");
		loadStr("check 2*a>a do a<<-a,..");
		parseFile();
		REQUIRE(vm->getVar("a")->value==-3);

		parseStr("check 2*a>a do a<<-a,..");
		REQUIRE(vm->getVar("a")->value==-3);

		parseStr("normal b c d<<256,.");
		parseStr("b<<255,.");
		parseStr("c<<254,.");
		parseStr("check b<d do check b>c do c<<0,...");
		REQUIRE(vm->getVar("c")->value==0);

		parseStr("check c do b<<228,..");
		REQUIRE(vm->getVar("b")->value==255);

		parseStr("check c*b+d do c<<1,..");
		REQUIRE(vm->getVar("c")->value==1);
		
		parseStr("check c*b+d do check c-a do check c-1 do c<<0,....");
		REQUIRE(vm->getVar("c")->value==1);
		
		parseStr("check c*b+d do a<<c, check c-a do a<<8, check c-1 do c<<0,....");
		REQUIRE(vm->getVar("c")->value==1);
		REQUIRE(vm->getVar("a")->value==1);

		parseStr("check c*b+d do a<<c, check c-a<=0 do a<<8, check c-1 do c<<0,....");
		REQUIRE(vm->getVar("c")->value==1);
		REQUIRE(vm->getVar("a")->value==8);

		parseStr("check c*d+a-b+c<d=>m*4 do a<<1,..");
		REQUIRE(err_vec.back().error_code==Err::undefined);

		parseStr("check 0 do a<<1488,..");
		REQUIRE(vm->getVar("a")->value==8);

		parseStr("check -1 do a<<1488,..");
		REQUIRE(vm->getVar("a")->value==(VarMap::size_table[VarType::small]-1));

		cleanCompileVars();
	}
}

TEST_CASE("until loops")
{
	SECTION("standard tests")
	{
		parseStr("normal a b c d<<256,.");
		parseStr("normal k<<1,.");
		parseStr("until a<2 do a<<a/2, k<<(1+k),..");
		REQUIRE(vm->getVar("k")->value==9);
		REQUIRE(vm->getVar("a")->value==1);

		parseStr("until k<=1 do a<<a*2, k<<(k-1),..");
		REQUIRE(vm->getVar("a")->value==256);
		REQUIRE(vm->getVar("k")->value==1);

		parseStr("until 1 do a<<1,..");
		REQUIRE(vm->getVar("a")->value==256);

		//to be debugged
	//	parseStr("field small small ff<<-1,.");
	//	parseStr("a<<32,.");
	//	parseStr("b<<31,.");
	//	parseStr("until a<0 do b<<31, a<<(a-1), until b<0 do ff[a b]<<2, b<<(b-1),...");
	//	std::cout<<*vm;

	//	int k=0;
	//	for(auto& v: dynamic_cast<Field*>(vm->getVar("ff"))->matr)
	//	{
	//		std::cout<<"KKKKKK: "<<k<<std::endl;
	//		REQUIRE(v->value==2);
	//		k++;
	//	}

		parseStr("b<<3,.");
		parseStr("c<<5,.");
		parseStr("d<<10,.");
		parseStr("a<<0,.");
		parseStr("until a+b*(c/d) do a<<(b*c)/d,..");
		REQUIRE(vm->getVar("a")->value==1);

		parseStr("a<<0,.");
		parseStr("b<<1023,.");
		parseStr("k<<0,.");
		parseStr("until a/b do k<<(k+1), b<<(b-1),..");
		REQUIRE(vm->getVar("b")->value==0);
		REQUIRE(vm->getVar("k")->value==1023);

		parseStr("until a do a<<1,..");
		REQUIRE(vm->getVar("a")->value==1);

		parseStr("until GG do a<<228,..");
		REQUIRE(err_vec.back().error_code==Err::undefined);

		parseStr("a<<5,.");
		parseStr("b<<5,.");
		parseStr("c<<5,.");
		parseStr("k<<0,.");
		parseStr("until a<=0 do b<<5, until b<=0 do c<<5, until c<=0 do k<<(k+1), c<<(c-1),. b<<(b-1),. a<<(a-1),..");
		REQUIRE(vm->getVar("k")->value==125);


		//aka fibonachhi with loops(not fruit ones)
		parseStr("normal k1 k2 result<<1,.");
		parseStr("a<<5,.");
		parseStr("until a<=0 do result<<(k1+k2), k1<<k2, k2<<result, a<<(a-1),..");
		REQUIRE(vm->getVar("result")->value==13);

		//to be debugged in a simplier version
	//	parseStr("a<<32,.");
	//	parseStr("b<<31,.");
	//	parseStr("k<<3,.");
	//	parseStr("until a<0 do b<<32, a<<(a-1), until b<0 do b<<(b-1), k<<4, until k<=0 do k<<(k-1), ff[a b]<<(ff[a b]*ff[a b]),....");
	//	for(auto& v: dynamic_cast<Field*>(vm->getVar("ff"))->matr)
	//	{
	//		REQUIRE(v->value==8);
	//	}

		cleanCompileVars();
	}
}

TEST_CASE("loops and conditions combined")
{
	SECTION("conditions inside loops")
	{
		parseStr("normal a b c d<<625,.");
		parseStr("tiny condition<<0,.");
		
		parseStr("until condition do a<<a/5, check a<=5 do condition<<1,...");
		REQUIRE(vm->getVar("a")->value==5);

		parseStr("condition<<0,.");
		parseStr("small con<<4,.");
		parseStr("until condition do check con do con<<(con-1),. check con<=0 do condition<<1,. @-1000, @con, @condition, @-1000,..");
		REQUIRE(vm->getVar("con")->value==0);

		parseStr("a<<20,.");
		parseStr("b<<20,.");
		parseStr("normal k<<0,.");
		parseStr("until a<0 do b<<20, until b<0 do check a<=b do check a=>b do k<<(k+1),.. b<<(b-1),. a<<(a-1),..");
		REQUIRE(vm->getVar("k")->value==21);

		parseStr("a<<20,.");
		parseStr("b<<20,.");
		parseStr("condition<<0,.");
		parseStr("k<<0,.");
		parseStr("until condition do b<<20, until b<0 do check a<=b do check a=>b do @-1000, @a, @b,@-1000, k<<(k+1),.. b<<(b-1),. a<<(a-1), check a<0 do condition<<1,...");
		REQUIRE(vm->getVar("k")->value==21);

		cleanCompileVars();
	}
	SECTION("loops inside conditions")
	{
		parseStr("normal a b c d<<25,.");
		parseStr("tiny condition<<0,.");

		//aka factorial with loops
		parseStr("c<<1,.");
		parseStr("a<<5,.");
		parseStr("check a>1 do until a<=0 do c<<c*a, a<<(a-1),...");
		REQUIRE(vm->getVar("c")->value==120);
		
		//aka number to binary

		parseStr("normal power<<0,.");
		parseStr("normal div<<b/2,.");
		parseStr("tiny digit<<0,.");
		parseStr("normal res<<0,.");
		parseStr("b<<10,.");
		parseStr("big pow<<1,.");
		parseStr("small order<<1,.");
	
		parseStr("until b<=0 do div<<b/2, digit<<(b-2*div), check power<=0 do check power=>0 do res<<(res+digit),.. check power<=1 do check power=>1 do res<<(res+digit*10),.. check power>1 do order<<power, until order<=0 do pow<<(pow*10), order<<(order-1),. res<<(res+digit*pow),. pow<<1, power<<(power+1), b<<(b/2),..");
		REQUIRE(vm->getVar("res")->value==1010);
		
		cleanCompileVars();
	}
}








