#include <Generator.h>
#include <iostream>
#include <fstream>


int main(int argc, char* argv[])
{
	int lines=1;
	if(argc>=2) lines=std::stoi(argv[1]);

	Generator gen{3, 5, 3};

	if(argc==3) 
	{
		if(std::string(argv[2])=="--correct")
		{
			for(int i=0; i<lines; i++) std::cout<<gen.genCorrectString()<<std::endl;
		}
		else if(std::string(argv[2])=="--incorrect")
		{
			for(int i=0; i<lines; i++) std::cout<<gen.genIncorrectString(Generator::incorrect_cases)<<std::endl;
		}
	}
	else
	{
		for(int i=0; i<lines; i++) std::cout<<gen.genLine()<<std::endl;
	}
	return  0;
}
