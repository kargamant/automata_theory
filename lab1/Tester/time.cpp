#include <Generator.h>
#include <Tester.h>
#include <iostream>
#include <string>
#include <time.h>
#include <regex>


int main()
{

	int varLength, maxSpacesLength, words;
	std::cout<<"Input varLength, maxSpacesLength, words: ";
	std::cin>>varLength>>maxSpacesLength>>words;

	Generator generator{varLength, maxSpacesLength, words};
	Tester tester{generator};
	
	std::cout<<"Now enter number of timing lines: "<<std::endl;
	int timingLines;
	std::cin>>timingLines;

	std::cout<<"generation:"<<std::endl;
	std::vector<std::string> str_vec;
	for(int i=0; i<timingLines; i++)
	{
		str_vec.push_back(generator.genLine());		
	}

	std::cout<<"timing:"<<std::endl;
	std::cout<<"	smc flex regex"<<std::endl;
	//tester.clearTimingData();
	int max_lines=timingLines;
	while(timingLines!=0)
	{
		std::vector<int> reses=tester.timing(str_vec);
		std::cout<<timingLines<<" "<<reses[0]<<" "<<reses[1]<<" "<<reses[2]<<std::endl;
		timingLines-=0.1*max_lines;
		str_vec.resize(timingLines);
		//std::cout<<timingLines<<" remain"<<std::endl;
	}
	//tester.displayResultsTable();
	return 0;
}
