#include "FlexRecognizer.h"
#include <iostream>
#include <sstream>

bool FlexRecognizer::checkString(std::string& str)
{
	std::stringstream st{str};
	switch_streams(&st, &std::cout);
	return yylex();
}


/*void FlexRecognizer::run(std::istream& in, std::ostream& out)
{
	in.unsetf(in.skipws);
	char c=0;
	std::string line;
	while(!in.eof())
	{
		while(c!='\n')
		{
			in>>c;
			if(in.eof()) 
			{
				break;
			}
			line+=c;
		}
		if(in.eof()) break;
		bool result=checkString(line);
		line.pop_back();
		out<<line<<": "<<result<<std::endl;
		line="";
		c=0;
	}
}*/
