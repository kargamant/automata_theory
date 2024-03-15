#include <iostream>
#include <string>
#include <time.h>
#include "Generator.h"
#include <regex>
#include <random>
#include <time.h>

std::string Generator::genNum(int length)
{
	std::string result;
	for(int i=0; i<length; i++) 
	{
		char c=48+std::rand()%10;
		result+=c;
	}
	return result;
}
char Generator::genChar(bool lowerCase)
{
	if(!lowerCase) return 65+std::rand()%26;
	else return 97+std::rand()%26;
}

char Generator::genBadChar()
{
	char c=32+std::rand()%15;
	while(c=='\'' || c=='"')
	{
		c=32+std::rand()%15;
	}
	return c;
}

int Generator::genChoice(int options)
{
	return std::rand()%options;
}

std::string Generator::genId(int length)
{
	std::string result;
	result+=genChar(genChoice());
	for(int i=1; i<length; i++)
	{
		int choice=genChoice();
		if(choice) result+=genNum();
		else result+=genChar(genChoice());
	}
	return result;
}

std::string Generator::genStringLiteral(int length, bool doubleQoutes)
{
	std::string result;
	if(doubleQoutes) result+="\"";
	else result+="\'";
	for(int i=0; i<length; i++)
	{
		int choice=genChoice();
		if(choice) result+=genBadChar();
		else
		{
			choice=genChoice();
			result+=genChar(choice);
		}
	}
	if(doubleQoutes) result+="\"";
	else result+="\'";
	return result;
}

std::string Generator::genSpaces(int length)
{
	std::string result;
	for(int i=0; i<length; i++) result+=" ";
	return result;
}

std::string Generator::genCorrectString()
{
	std::string result;
	result+="for";
	result+=genSpaces(1+std::rand()%maxSpacesLength);
	result+=genId(varLength);
	result+=genSpaces(1+std::rand()%maxSpacesLength);
	result+="in";
	result+=genSpaces(1+std::rand()%maxSpacesLength);
	result+="(";
	result+=genSpaces(1+std::rand()%maxSpacesLength);
	for(int i=0; i<words; i++)
	{
		int choice=genChoice(3);
		if(choice==0)
		{
			result+=genId(1+std::rand()%varLength);
		}
		else if(choice==1)
		{
			result+=genStringLiteral(1+std::rand()%varLength, genChoice());
		}
		else
		{
			result+=genNum(1+std::rand()%varLength);
		}
		result+=genSpaces(1+std::rand()%maxSpacesLength);
	}
	result+=")";
	return result;
}

std::string Generator::genAbsRandString(int length)
{
	std::string result;
	for(int i=0; i<length; i++)
	{
		int choice=genChoice();
		if(choice)
		{
			char c=genBadChar();
			while(c==' ' || c==0)
			{
				c=genBadChar();
			}
			result+=genBadChar();
		}
		else
		{
			result+=genChar();
		}
	}
	return result;
}


std::string Generator::genIncorrectString(std::vector<std::string> cases)
{
	//std::srand(time(NULL));
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























