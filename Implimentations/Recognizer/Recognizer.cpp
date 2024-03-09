#include "Recognizer.h"
#include <iostream>

void Recognizer::run(std::istream& in, std::ostream& out)
{
	in.unsetf(in.skipws);
	while(!in.eof())
	{
		while(lastChar!='\n')
		{
			in>>lastChar;
			if(in.eof()) 
			{
				break;
			}
			line+=lastChar;
		}
		if(in.eof()) break;
		bool result=checkString(line);
		line.pop_back();
		out<<line<<": "<<result<<std::endl;
		line="";
		lastChar=0;
	}
}