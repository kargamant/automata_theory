#include <iostream>
#include <string>
#include <chrono>
#include <Generator.h>
#include <regex>
#include <random>

void Generator::updateSeed()
{
	std::random_device rd;
	engine.seed(rd());
	//engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}

std::string Generator::genNum(int length)
{
	//updateSeed();
	std::uniform_int_distribution<int> db(48, 57); 

	std::string result;
	result.reserve(length);
	std::generate_n(std::back_inserter(result), length, [&]() mutable {return db(engine);});
	return result;
}
char Generator::genChar(bool lowerCase)
{
	//updateSeed();
	if(!lowerCase) 
	{
		std::uniform_int_distribution<int> db(65, 90);
		return db(engine);
	}
	else 
	{
		std::uniform_int_distribution<int> db(97, 122);
		return db(engine);
	}
}

char Generator::genBadChar()
{
	constexpr char badChars[11]={33, 35, 36, 37, 38, 40, 41, 42, 43, 44, 45};
	//updateSeed();
	std::discrete_distribution<int> db(0, 10);
	return badChars[db(engine)];
}

int Generator::genChoice(int options)
{
	//updateSeed();
	std::uniform_int_distribution<int> db(0, options);
	return db(engine);
}

std::string Generator::genId(int length)
{
	std::string result;
	result.reserve(length);
	result+=genChar(genChoice());
	
	std::generate_n(std::back_inserter(result), length-1, [&]() mutable {return genChoice() ? genNum()[0] : genChar(genChoice());});
	return result;
}

std::string Generator::genStringLiteral(int length, bool doubleQoutes)
{
	std::string result;
	result.reserve(length+2);

	if(doubleQoutes) result+="\"";
	else result+="'";
	
	std::generate_n(std::back_inserter(result), length, [&]() mutable {return genChoice() ? genBadChar() : genChar(genChoice());} );

	if(doubleQoutes) result+="\"";
	else result+="'";
	return result;
}

std::string Generator::genSpaces(int length)
{
	return std::string(length, ' ');
}

std::string Generator::genCorrectString()
{
	std::string result;
	result.reserve(7+varLength*(words+1)+maxSpacesLength*(5+words));	
	
	//updateSeed();
	std::uniform_int_distribution<int> db_spaces(1, maxSpacesLength);
	result+="for";
	result+=genSpaces(db_spaces(engine));
	result+=genId(varLength);
	result+=genSpaces(db_spaces(engine));
	result+="in";
	result+=genSpaces(db_spaces(engine));
	result+="(";
	result+=genSpaces(db_spaces(engine));
	
	for(int i=0; i<words; i++)
	{
		updateSeed();
		int choice=genChoice(3);
		std::uniform_int_distribution<int> db_var(1, varLength);

		if(choice==0)
		{
			result+=genId(db_var(engine));
		}
		else if(choice==1)
		{
			result+=genStringLiteral(db_var(engine), genChoice());
		}
		else
		{
			result+=genNum(db_var(engine));
		}
		result+=genSpaces(db_spaces(engine));
	}
	result+=")";
	return result;
}

std::string Generator::genAbsRandString(int length)
{
	std::string result;
	result.reserve(length);

	std::generate_n(std::back_inserter(result), length, [&]() mutable {return genChoice() ? genBadChar() : genChar();});
	return result;
}


std::string Generator::genIncorrectString(const std::vector<std::string>& cases)
{
	int choice=genChoice(cases.size());
	std::string result=cases[choice];
	result=std::regex_replace(result, std::regex("<var>"), genId(varLength));
	result=std::regex_replace(result, std::regex("<abs_rand>"), genAbsRandString(varLength));
	result=std::regex_replace(result, std::regex("<int>"), genNum());
	return result;
	//cases
	//<abs_rand>
	//for <abs_rand>
	//for <abs_rand> in
	//for  in <abs_rand>
	//for <var> in (
	//for <var> in )
	//for <var> in ()
	//for <var> in (<abs_rand>)
	//for    <var>   <abs_rand>    in ()
	//for    <var>    in()
	//for    <int><var>     in  ()
	//for <var>    in ( )
	//for <var>  in ('<abs_rand>)
	//for <var>  in (<abs_rand>')
	//for <var>  in ("<abs_rand>)
	//for <var>  in (<abs_rand>")
	//for <var>  in (         "<abs_rand>"<var>  )
	//for <var>  in (         "<abs_rand>"<int>  )
	//for <var>  in (         "<abs_rand>"<other string literal>  )
	//for <var>  in (         <var>"<abs_rand>"  )
	//for <var>  in (         <int>"<abs_rand>"  )
	//for <var>  in (         <other string literal>"<abs_rand>"  )
}























