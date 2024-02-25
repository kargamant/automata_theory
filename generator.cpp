#include <iostream>
#include <string>
#include <time.h>

char genNum()
{
	return 48+std::rand()%10;
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

bool genChoice()
{
	return std::rand()%2;
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
//std::string genCorrectString(int varLength, int words);
//std::string genIncorrectString();

int main()
{
	std::srand(time(NULL));
	int length=0;
	std::cin>>length;
	std::cout<<genId(length)<<std::endl;
	std::cout<<genStringLiteral(length)<<std::endl;
	return 0;
}
