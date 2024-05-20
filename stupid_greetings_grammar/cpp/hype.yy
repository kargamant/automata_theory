%require "3.5"
%language "c++"


%code requires {
	#include "hype.tab.hh"
	class Interpreter;
}
%define api.value.type variant
%define api.token.constructor
%param {Interpreter& intrpr}
%code {
	#include "Interpreter.h"
}

%code requires
{
	#include <iostream>
}


%token <std::string> HELLO
%token <int> ID

%%
gretings:
	HELLO ID {
			std::cout<<"Yes, I am "<<$2<<std::endl;
		}
%%
