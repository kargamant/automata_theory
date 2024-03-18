#include <Generator.h>
#include <Tester.h>
#include <iostream>
#include <string>
#include <time.h>
#include <regex>


int main()
{
	//entering data
	int varLength, maxSpacesLength, words;
	std::cout<<"Input varLength, maxSpacesLength, words: ";
	std::cin>>varLength>>maxSpacesLength>>words;

	std::cout<<"Now enter number of timing lines: "<<std::endl;
	int timingLines;
	std::cin>>timingLines;
	

	Generator generator{varLength, maxSpacesLength, words};
	Tester tester;

	std::cout<<"generation:"<<std::endl;
	
	std::vector<std::string> str_vec;
	str_vec.reserve(timingLines);
	std::generate_n(std::back_inserter(str_vec), timingLines, [&](){return generator.genLine();});

	std::cout<<"timing:"<<std::endl;
	tester.clearTimingData();
	tester.timingFromTo(str_vec, timingLines, 0, 0.1);
	tester.writeResults();
	//tester.displayResultsTable();
	return 0;
}
