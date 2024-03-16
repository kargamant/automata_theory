#include "Generator/Generator.h"
#include "Tester/Tester.h"
#include <iostream>
#include <string>
#include <time.h>
#include <regex>


int main()
{

	std::srand(time(NULL));
	int varLength, maxSpacesLength, words;
	std::cout<<"Input varLength, maxSpacesLength, words: ";
	std::cin>>varLength>>maxSpacesLength>>words;

	Generator generator{varLength, maxSpacesLength, words};
	Tester tester{generator};
	
	std::cout<<"Now enter number of timing lines: "<<std::endl;
	int timingLines;
	std::cin>>timingLines;

	std::cout<<"timing:"<<std::endl;
	tester.clearTimingData();
	while(timingLines!=0)
	{
		tester.timing(timingLines, timeMode::incorrectOnly);
		timingLines-=50000;
		std::cout<<timingLines<<" remain"<<std::endl;
	}
	tester.displayResultsTable();
	return 0;
}
