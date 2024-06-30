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
		
		parseStr("big calcPow normal a normal n begin check n<=0 do return 1,. check n<=1 do return a,. big res<<1, until n<=0 do res<<(res*a), n<<(n-1),. return res,. end,.");
		parseStr("normal OO<<calcPow(2 4),.");
		REQUIRE(vm->getVar("OO")->value==16);

		parseStr("big LL<<(1+3)*OO+calcPow(2 6),.");
		REQUIRE(vm->getVar("LL")->value==128);

		parseStr("big HH<<HH,.");
		REQUIRE(err_vec.back().error_code==Err::undefined);

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
	SECTION("different expressions to variable")
	{
		parseStr("normal a b c d<<25,.");

		parseStr("tiny invert tiny a begin check a<=0 do return 1,. check a=>1 do return 0,.. end,.");
		parseStr("a<<c*invert(c),.");
		REQUIRE(vm->getVar("a")->value==0);
		
		parseStr("c<<3,.");
		parseStr("b<<(a+c*(d/b)),.");
		REQUIRE(vm->getVar("b")->value==3);
		
		parseStr("b<<(a+(c*d)/b),.");
		REQUIRE(vm->getVar("b")->value==25);

		parseStr("invert(0)>>c,.");
		REQUIRE(vm->getVar("c")->value==1);

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
		//std::cout<<program_stack.top();

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
	SECTION("different expressions to variable")
	{
		loadStr("normal a b c<<55,");
		loadStr("big calcPow normal a normal n begin check n<=0 do return 1,. check n<=1 do return a,. big res<<1, until n<=0 do res<<(res*a), n<<(n-1),. return res,. end,");
		
		loadStr("calcPow(3 4)>>a<<calcPow(4 3),.");
		parseFile();
		REQUIRE(vm->getVar("a")->value==64);
		cleanProgStack();

		//parseStr("@-7000, @a, @b, @c, @(a*calcPow(2 2)-c), @-7000,.");
		loadStr("normal a b c<<55,");
		loadStr("a<<64,");
		loadStr("c<<(a*calcPow(2 2)-c)>>b<<(a*calcPow(2 2)+c),.");
		parseFile();
		REQUIRE(vm->getVar("b")->value==311);
		REQUIRE(vm->getVar("c")->value==201);
		
		parseStr("b<<c<<55,.");
		parseStr("c<<(a*calcPow(2 2)-b)>>b<<(a*calcPow(2 2)+b),.");
		REQUIRE(vm->getVar("b")->value==457);
		REQUIRE(vm->getVar("c")->value==201);

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

		parseStr("8>>a>>b,.");
		parseStr("3>>c>>d,.");
		parseStr("small remainder big a normal div begin return (-a/div)*div+a,.end,.");
		parseStr("((a+b/2)+(b/2+c/2)+(c/2+d/2)+d/2+remainder(c 2)+remainder(d 2))>>d,.");
		REQUIRE(vm->getVar("d")->value==22);

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

		parseStr("8>>a>>b,.");
		parseStr("3>>c>>d,.");
		parseStr("(-a)*(-b)-a*b+c*(-d)>>d,.");
		REQUIRE(vm->getVar("d")->value==-9);

		parseStr("d<<(-3-(-3)),.");
		REQUIRE(vm->getVar("d")->value==0);
		
		parseStr("small remainder big a normal div begin return (-a/div)*div+a,.end,.");
		parseStr("d<<(a-remainder(a 3)),.");
		REQUIRE(vm->getVar("d")->value==6);

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

		parseStr("((-d)*d/(-c)+a)>>b,.");
		REQUIRE(vm->getVar("b")->value==-29);

		parseStr("((-d)*d/((-c)+a))>>b,.");
		REQUIRE(vm->getVar("b")->value==-12);
		
		parseStr("small remainder big a normal div begin return (-a/div)*div+a,.end,.");
		parseStr("b<<-b,.");
		parseStr("a<<remainder(b 5),.");
		parseStr("d<<(b-(b/5)*5),.");
		REQUIRE(vm->getVar("a")->value==vm->getVar("d")->value);

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

		parseStr("a<<1,.");
		parseStr("b<<0,.");
		parseStr("a<<a>b>>b,.");
		REQUIRE(vm->getVar("a")->value==0);
		REQUIRE(vm->getVar("b")->value==1);

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
	//	parseStr("a<<3,.");
	//	parseStr("b<<-100,.");
	//	parseStr("c<<50,.");
	//	parseStr("d<<140,.");
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

		parseStr("field big small ff<<-1,.");
		parseStr("a<<31,.");
		parseStr("b<<31,.");
		parseStr("until a<0 do b<<31, until b<0 do ff[a b]<<2, b<<(b-1),. a<<(a-1),..");

		int k=0;
		for(auto& v: dynamic_cast<Field*>(vm->getVar("ff"))->matr)
		{
			std::cout<<"KKKKKK: "<<k<<std::endl;
			REQUIRE(v->value==2);
			k++;
		}

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
		parseStr("a<<31,.");
		parseStr("b<<31,.");
		parseStr("k<<3,.");
		parseStr("until a<0 do b<<31, until b<0 do k<<3, until k<=0 do ff[a b]<<(ff[a b]*2), k<<(k-1),. @-90000, @ff[31 30], @-90000, b<<(b-1),. a<<(a-1),..");
		std::cout<<*vm;
		k=0;
		for(auto& v: dynamic_cast<Field*>(vm->getVar("ff"))->matr)
		{
			std::cout<<"KKKKKK: "<<k<<std::endl;
			REQUIRE(v->value==8);
			k++;
		}

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

TEST_CASE("Functions")
{
	SECTION("Definition and simple calls")
	{
		parseStr("big addOne big a begin return (a+1),. end,.");
		REQUIRE(declared_funcs.contains("addOne"));

		parseStr("normal b<<addOne(1),.");
		REQUIRE(vm->getVar("b")->value==2);

		parseStr("b<<addOne(b),.");
		REQUIRE(vm->getVar("b")->value==3);

		parseStr("tiny invert tiny a begin check a<=0 do return 1,. check a=>1 do return 0,.. end,.");
		REQUIRE(declared_funcs.contains("invert"));

		parseStr("b<<0,.");
		parseStr("tiny res<<invert(b),.");
		REQUIRE(vm->getVar("res")->value==1);

		parseStr("b<<res,.");
		parseStr("res<<invert(b),.");
		REQUIRE(vm->getVar("res")->value==0);

		parseStr("big GG<<256,.");
		parseStr("res<<invert(GG),.");
		REQUIRE(vm->getVar("res")->value==0);

		parseStr("GG<<-30,.");
		parseStr("res<<invert(GG),.");
		REQUIRE(vm->getVar("res")->value==1);

		parseStr("GG<<100000,.");
		parseStr("GG<<addOne(GG),.");
		REQUIRE(vm->getVar("GG")->value==(VarMap::size_table[VarType::big]-1));

		parseStr("GG<<func(1 2 3 4 5),.");
		REQUIRE(err_vec.back().error_code==Err::undefined);

		parseStr("normal sum5 normal a normal b normal c begin return (a+b+c),. end,.");
		REQUIRE(declared_funcs.contains("sum5"));

		parseStr("GG<<sum5(512 256 256),.");
		REQUIRE(vm->getVar("GG")->value==(VarMap::size_table[VarType::normal]-1));
		
		cleanCompileVars();
	}
	SECTION("usage in loops and conditions")
	{
		parseStr("big addOne big a begin return (a+1),. end,.");

		parseStr("normal a<<0,.");
		parseStr("normal b<<1,.");
		parseStr("normal k<<10,.");
		parseStr("until k<=0 do a<<(a+b), b<<addOne(b), k<<(k-1),..");
		REQUIRE(vm->getVar("a")->value==55);

		//also example of how local variable res is prioritized above global one in function
		parseStr("big calcPow normal a normal n begin check n<=0 do return 1,. check n<=1 do return a,. normal res<<1, until n<=0 do res<<(res*a), n<<(n-1),. return res,. end,.");
		parseStr("normal power<<0,.");
		parseStr("normal div<<b/2,.");
		parseStr("tiny digit<<0,.");
		parseStr("normal res<<0,.");
		parseStr("b<<10,.");
	
		parseStr("until b<=0 do div<<b/2, digit<<(b-2*div), res<<(res+digit*calcPow(10 power)), power<<(power+1), b<<(b/2),..");
		REQUIRE(vm->getVar("res")->value==1010);

		parseStr("big bin normal b begin normal div<<b/2, tiny digit<<0, normal res power<<0, until b<=0 do div<<b/2, digit<<(b-2*div), res<<(res+digit*calcPow(10 power)), power<<(power+1), b<<(b/2),. return res,. end,.");
		
		parseStr("b<<7,.");
		parseStr("res<<bin(b),.");
		REQUIRE(vm->getVar("res")->value==111);
		
		parseStr("tiny isDivBy normal a normal div begin normal remainder<<(a-(a/div)*div), check remainder<=0 do check remainder=>0 do return 1,.. return 0,. end,.");
		parseStr("a<<10,.");
		parseStr("tiny gg<<0,.");
		parseStr("b<<bin(a),.");
		parseStr("check isDivBy(a 2) do gg<<isDivBy(b 2),..");
		REQUIRE(vm->getVar("gg")->value==1);

		parseStr("gg<<0,.");
		parseStr("a<<2,.");
		parseStr("a<<calcPow(a 3)*calcPow(a 3)*calcPow(a 3),.");
		parseStr("check a<=512 do check a=>512 do gg<<1,...");
		REQUIRE(vm->getVar("gg")->value==1);
		
		cleanCompileVars();
	}
	SECTION("Tricky situations")
	{
		//trying to reach global vars from function
		parseStr("big lastArg<<0,.");
		parseStr("big addOne big a begin lastArg<<a, return (a+1),. end,.");

		parseStr("big result<<addOne(3),.");
		REQUIRE(vm->getVar("lastArg")->value==3);

		//should work like in python. If global var was defined after definition of function than it is a whole different variable
		parseStr("big addTwo big a begin lastArg2<<a, return (a+2),. end,.");
		parseStr("big lastArg2<<0,.");
		parseStr("result<<addTwo(5),.");
		REQUIRE(vm->getVar("lastArg2")->value==0);

		loadStr("big GG<<0,");
		loadStr("normal dd<<0,");
		loadStr("big foo big a begin normal dd<<a*2, normal res<<func(a), return dd,. end,");
		loadStr("big func big a begin dd<<a, return dd,. end,");
		loadStr("GG<<foo(2),");
		loadStr("@dd,.");
		parseFile();

		REQUIRE(program_stack.top()->getVar("dd")->value==0);
		REQUIRE(program_stack.top()->getVar("GG")->value==4);

		parseStr("big fof normal a begin return (kk+a),. end,.");
		parseStr("GG<<fof(3),.");
		REQUIRE(err_vec.back().error_code==Err::undefined);

		//2a if local, a-b if global
		parseStr("normal summ<<0,.");
		parseStr("big cool normal a normal b begin normal summ<<(a+b), big res<<cool2(a b), return res,. end,.");
		parseStr("big cool2 normal a normal b begin normal result<<(a-b+summ), return result,. end,.");
		parseStr("normal a b<<2,.");
		parseStr("a<<1,.");
		parseStr("b<<4,.");
		parseStr("GG<<cool(a b),.");
		REQUIRE(program_stack.top()->getVar("GG")->value==-3);

		parseStr("big hype normal t begin t>>5,. end,.");
		parseStr("GG<<hype(6),.");
		REQUIRE(err_vec.back().error_code==Err::invalidAssign);
		
		cleanCompileVars();
	}
}

TEST_CASE("robot")
{
	SECTION("basic operations")
	{
		labirint=Map(8, 8);
		std::cout<<labirint;

		parseStr("go,.");
		REQUIRE(labirint.getRobo().getX()==0);
		REQUIRE(labirint.getRobo().getY()==1);
		REQUIRE(labirint.getRobo().getAngle()==30);

		parseStr("go,.");
		REQUIRE(err_vec.back().error_code==Err::roboError);

		parseStr("rl,.");
		REQUIRE(labirint.getRobo().getAngle()==90);

		parseStr("rl,.");
		REQUIRE(labirint.getRobo().getAngle()==150);

		parseStr("rl,.");
		REQUIRE(labirint.getRobo().getAngle()==210);

		parseStr("rl,.");
		REQUIRE(labirint.getRobo().getAngle()==270);

		parseStr("rl,.");
		REQUIRE(labirint.getRobo().getAngle()==330);

		parseStr("rl,.");
		REQUIRE(labirint.getRobo().getAngle()==30);

		parseStr("rr,.");
		REQUIRE(labirint.getRobo().getAngle()==330);

		parseStr("rr,.");
		REQUIRE(labirint.getRobo().getAngle()==270);

		parseStr("rr,.");
		REQUIRE(labirint.getRobo().getAngle()==210);

		parseStr("rr,.");
		REQUIRE(labirint.getRobo().getAngle()==150);

		parseStr("rr,.");
		REQUIRE(labirint.getRobo().getAngle()==90);

		parseStr("rr,.");
		REQUIRE(labirint.getRobo().getAngle()==30);

		bool flip=false;
		for(int i=0; i<6; i++)
		{
			if(!flip)
			{
				parseStr("rr,.");
			}
			else
			{
				parseStr("rl,.");
			}
			parseStr("go,.");
			flip=!flip;
		}
		REQUIRE(labirint.getRobo().getX()==0);
		REQUIRE(labirint.getRobo().getY()==7);
		
		parseStr("rr,.");
		parseStr("rr,.");
		for(int i=0; i<7; i++)
		{
			parseStr("go,.");
		}
		REQUIRE(labirint.getRobo().getX()==7);
		REQUIRE(labirint.getRobo().getY()==7);

		labirint.transportRobo(3, 3);		
		//10101
		labirint.changeCellType(4, 3, CellType::obstacle);
		labirint.changeCellType(2, 4, CellType::obstacle);
		labirint.changeCellType(3, 2, CellType::obstacle);
		parseStr("small report<<sonar,.");
		REQUIRE(vm->getVar("report")->value==21);

		labirint.transportRobo(0, 0);
		parseStr("rr,.");
		labirint.changeCellType(1, 0, CellType::obstacle);
		//11011
		parseStr("report<<sonar,.");
		REQUIRE(vm->getVar("report")->value==27);
	}
	SECTION("usage with other constructions")
	{
		labirint.transportRobo(0, 1);
		parseStr("rl,.");		
		parseStr("rl,.");		
		parseStr("rl,.");		
		
		//flip loop but completely in interpreted langugage
		parseStr("tiny flip<<0,.");
		parseStr("small k<<6,.");
		parseStr("tiny invert tiny a begin check a<=0 do return 1,. check a=>1 do return 0,.. end,.");
		parseStr("until k<=0 do check flip<=0 do rr,. check flip=>1 do rl,. go, flip<<invert(flip), k<<(k-1),..");
		REQUIRE(labirint.getRobo().getX()==0);
		REQUIRE(labirint.getRobo().getY()==7);

		parseStr("rr,.");
		parseStr("rr,.");
		parseStr("k<<7,.");
		parseStr("until k<=0 do go, k<<(k-1),..");
		REQUIRE(labirint.getRobo().getX()==7);
		REQUIRE(labirint.getRobo().getY()==7);
		
		labirint.transportRobo(3, 3);		
		parseStr("big calcPow normal a normal n begin check n<=0 do return 1,. check n<=1 do return a,. big res<<1, until n<=0 do res<<(res*a), n<<(n-1),. return res,. end,.");
		parseStr("big bin normal b begin normal div<<b/2, tiny digit<<0, big res power<<0, until b<=0 do div<<b/2, digit<<(b-2*div), res<<(res+digit*calcPow(10 power)), power<<(power+1), b<<(b/2),. return res,. end,.");
		parseStr("big GG<<bin(sonar),.");
		REQUIRE(vm->getVar("GG")->value==10101);

		labirint=Map(8, 8);
		labirint.transportRobo(0, 1);
		std::cout<<labirint;
		parseStr("big traverseBorder normal b begin tiny flip<<0, small k<<6, until k<=0 do check flip<=0 do rr,. check flip=>1 do rl,. go, flip<<invert(flip), k<<(k-1),..end,.");
		//parseStr("big traverseBorder normal b begin tiny flip<<1, small k<<7, until k<=0 do check flip<=0 do rr,. check flip=>1 do rl,. go, flip<<invert(flip), k<<(k-1),. rr, k<<7, until k<=0 do go, k<<(k-1),. flip<<0, k<<7, until k<=0 do check flip<=0 do rr,. check flip=>1 do rl,. go, flip<<invert(flip), k<<(k-1),.. end,.");
		parseStr("GG<<traverseBorder(3),.");
		REQUIRE(labirint.getRobo().getX()==0);
		REQUIRE(labirint.getRobo().getY()==7);
	}

}





