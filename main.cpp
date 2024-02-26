#include "Generator/Generator.h"
#include "Tester/Tester.h"
#include <iostream>
#include <string>
#include <time.h>
#include <regex>


int main()
{
	/*std::cout<<"regex experiment: "<<std::endl;
	std::regex var("<var>");
	std::smatch results;
	std::string tested="for <var> in ( <var>\"hype\")";
	tested=std::regex_replace(tested, var, "haha");
	std::cout<<tested<<std::endl;*/
	/*std::cout<<"regex experiment: "<<std::endl;
	std::string tested="<int> + <var> +  in (  '<abs_rand>' )";
	std::vector<std::string> cases;
	cases.push_back(tested);
	Generator genZ{5, 2, 4};
	std::string incorrect=genZ.genIncorrectString(cases);
	std::cout<<"incorrect: "<<incorrect<<std::endl;*/

	std::srand(time(NULL));
	int varLength, maxSpacesLength, words;
	std::cout<<"Input varLength, maxSpacesLength, words: ";
	std::cin>>varLength>>maxSpacesLength>>words;
	Generator generator{varLength, maxSpacesLength, words};
	Tester tester{"pull.txt", "lab1", generator};
	tester.testAll(5);
	//std::cout<<generator.genCorrectString()<<std::endl;
	return 0;
}
