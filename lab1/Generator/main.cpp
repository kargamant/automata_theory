#include <Generator.h>
#include <iostream>
#include <fstream>

std::fstream openSafe(std::string fileName, std::ios_base::openmode mode)
{
	std::fstream fs(fileName, mode);
	if(!fs.is_open())
	{
		fs.close();
		fs.open(fileName, mode);
		fs.close();
		fs.open(fileName);
	}
	fs.unsetf(fs.skipws);
	return fs;
}

std::string readLine(std::fstream& fs)
{
	char c=0;
	std::string line;

	while(c!='\n' && !fs.eof()) 
	{
		fs>>c;
		if(c!='\n') line+=c;
	}
	return line;
}

int main(int argc, char* argv[])
{
	std::fstream load=openSafe("incorrect_cases.txt", std::ios::in);
	std::vector<std::string> cases;
	while(!load.eof())
	{
		cases.push_back(readLine(load));
	}
	int lines=1;
	if(argc>=2) lines=std::stoi(argv[1]);

	Generator gen{3, 5, 3};

	for(int i=0; i<lines; i++)
	{
		int choice;
		if(argc==3) 
		{
			if(std::string(argv[2])=="--correct") choice=1;
			else if(std::string(argv[2])=="--incorrect") choice=0;
			else choice=gen.genChoice(); 
		}
		else choice=gen.genChoice();
		if(choice)
		{
			std::cout<<gen.genCorrectString()<<std::endl;
		}
		else
		{
			std::cout<<gen.genIncorrectString(cases)<<std::endl;
		}
	}
	return  0;
}
