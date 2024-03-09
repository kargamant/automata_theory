#include "Translator.h"
#include <format>

namespace Translator
{

	Translator::Translator() : fsm(*this) //, fs("file.txt") 
	{
		/*if(!fs.is_open())
		{
			fs.clear();
			fs.open("file.txt", std::ios::out);
			fs.close();
			fs.open("file.txt", std::ios::in);
		}
		fs.unsetf(fs.skipws);*/
	}

	/*Translator::Translator(std::string& fileName) : fsm(*this), fs(std::fstream())
	{
		fs.open(fileName, std::ios::in);
		fs.unsetf(fs.skipws);
	}*/

	void Translator::correct(std::ostream& stream)
	{
		isCorrect=true;
	}
	
	void Translator::incorrect(std::ostream& stream)
	{
		isCorrect=false;
	}
	void Translator::run(std::istream& in, std::ostream& out)
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
			isCorrect=false;
			isStopped=false;
			lastChar=0;
		}
	}
	bool Translator::checkString(std::string& str)
	{
		for(char c: str)
		{
			lastChar=c;
			fsm.readNext();
			if(debugInfo) std::cout<<"last char: "<<lastChar<<" ; current state: "<<fsm.getState().getName()<<std::endl;
			if(isStopped || isCorrect) break;
		}
		return isCorrect;
	}
}
