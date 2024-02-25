#include <iostream>
#include <string>
#include <time.h>

std::string genNum(int length=1)
{
	std::string result;
	for(int i=0; i<length; i++) 
	{
		char c=48+std::rand()%10;
		result+=c;
	}
	return result;
}
char genChar(bool lowerCase=true)
{
	if(!lowerCase) return 65+std::rand()%26;
	else return 97+std::rand()%26;
}

char genBadChar()
{
	char c=32+std::rand()%15;
	while(c=='\'' || c=='"')
	{
		c=32+std::rand()%15;
	}
	return c;
}

int genChoice(int options=2)
{
	return std::rand()%options;
}

std::string genId(int length)
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

std::string genStringLiteral(int length, bool doubleQoutes=false)
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

std::string genSpaces(int length)
{
	std::string result;
	for(int i=0; i<length; i++) result+=" ";
	return result;
}

std::string genCorrectString(int varLength, int maxSpacesLength, int words)
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
std::string genIncorrectString();

int main()
{
	std::srand(time(NULL));
//	int length=0;
//	std::cin>>length;
//	std::cout<<genId(length)<<std::endl;
//	std::cout<<genStringLiteral(length)<<std::endl;
	int varLength, maxSpacesLength, words;
	std::cout<<"Input varLength, maxSpacesLength, words: ";
	std::cin>>varLength>>maxSpacesLength>>words;
	std::cout<<genCorrectString(varLength, maxSpacesLength, words)<<std::endl;
	return 0;
}
