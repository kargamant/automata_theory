#include <regex>
#include <iostream>
#include <format>
#include <fstream>

int main()
{
	char c=0;
	std::string line;

	std::string regexp;
	std::fstream reg("regexp.txt");
	reg.unsetf(reg.skipws);
	while(c!='\n' && !reg.eof()) 
	{
		reg>>c;
		if(c!='\n') regexp+=c;
	}
	reg.close();
	c=0;

	std::cout<<"finding matches with regexp: \""<<regexp<<"\""<<std::endl;
	std::regex re(regexp);
	std::fstream fs("../input.txt");
	if(!fs.is_open())
	{
		fs.close();
		fs.open("../input.txt", std::ios::in);
		fs.close();
		fs.open("../input.txt");
	}
	fs.unsetf(fs.skipws);
	while(!fs.eof())
	{
		while(c!='\n' && !fs.eof())
		{
			//std::cout<<c<<std::endl;
			fs>>c;
			if(c!='\n') line+=c;
		}
		std::smatch ms;
		if(std::regex_match(line, ms, re))
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
