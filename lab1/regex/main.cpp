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

int main()
{
	char c=0;
	std::string line;

	//reading regular expresiion
	std::fstream reg=openSafe("regexp.txt");
	std::string regexp=readLine(reg);
	reg.close();

	std::cout<<"finding matches with regexp: \""<<regexp<<"\""<<std::endl;
	std::regex re(regexp);
	
	//reading file with test strings
	std::fstream fs=openSafe("../input.txt");
	/*std::fstream fs("../input.txt");
	if(!fs.is_open())
	{
		fs.close();
		fs.open("../input.txt", std::ios::in);
		fs.close();
		fs.open("../input.txt");
	}
	fs.unsetf(fs.skipws);*/
	while(!fs.eof())
	{
		/*while(c!='\n' && !fs.eof())
		{
			//std::cout<<c<<std::endl;
			fs>>c;
			if(c!='\n') line+=c;
		}*/
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
		c=0;
	}
	fs.close();
	return 0;
}
