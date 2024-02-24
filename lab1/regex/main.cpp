#include <regex>
#include <iostream>
#include <format>
#include <fstream>

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

std::fstream openSafe(std::string fileName)
{
	std::fstream fs(fileName);
	fs.unsetf(fs.skipws);
	if(!fs.is_open())
	{
		fs.close();
		fs.open(fileName, std::ios::in);
		fs.close();
		fs.open(fileName);
	}
	return fs;
}

int main(int argc, char* argv[])
{
	if(argc<3) throw std::invalid_argument("Error. Not all files specified.");
	std::string line;

	//reading regular expresiion
	std::fstream reg=openSafe(argv[1]);
	std::string regexp=readLine(reg);
	reg.close();

	std::cout<<"finding matches with regexp: \""<<regexp<<"\""<<std::endl;
	std::regex re(regexp);
	
	//reading file with test strings
	std::fstream fs=openSafe(argv[2]);
	while(!fs.eof())
	{
		line=readLine(fs);

		//finding matches
		if(std::regex_match(line, re))
		{
			std::cout<<std::format("Line \"{}\" is correct", line)<<std::endl;
		}
		else
		{
			std::cout<<std::format("Line \"{}\" is incorrect", line)<<std::endl;
		}
		line="";
	}
	fs.close();
	return 0;
}
