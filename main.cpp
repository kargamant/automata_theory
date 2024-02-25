#include "Generator/Generator.h"
#include "Tester/Tester.h"
#include <iostream>
#include <string>
#include <time.h>


int main()
{
	std::srand(time(NULL));
	int varLength, maxSpacesLength, words;
	std::cout<<"Input varLength, maxSpacesLength, words: ";
	std::cin>>varLength>>maxSpacesLength>>words;
	Generator generator{varLength, maxSpacesLength, words};
	Tester tester{"pull.txt", "lab1", generator};
	tester.testAll();
	//std::cout<<generator.genCorrectString()<<std::endl;
	return 0;
}
