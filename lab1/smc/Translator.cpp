#include "Translator.h"
#include <format>

namespace Translator
{

	Translator::Translator() : fsm(*this), fs("file.txt") 
	{
		if(!fs.is_open())
		{
			fs.clear();
			fs.open("file.txt", std::ios::out);
			fs.close();
			fs.open("file.txt", std::ios::in);
		}
		fs.unsetf(fs.skipws);
	}

	Translator::Translator(std::string& fileName) : fsm(*this), fs(std::fstream())
	{
		fs.open(fileName, std::ios::in);
		fs.unsetf(fs.skipws);
	}

	void Translator::readNext()
	{
		if(fs.eof()) lastChar=0;
		else fs>>lastChar;
		if(lastChar!='\n') line+=lastChar;
		if(debugInfo) std::cout<<"last char: "<<lastChar<<" ; current state: "<<fsm.getState().getName()<<std::endl;
		fsm.readNext();
	}


	void Translator::correct(std::ostream& stream)
	{
		if(outputInfo) stream<<std::format("Processed line: \"{}\" is correct", line)<<std::endl;
		line="";
	}
	
	void Translator::incorrect(std::ostream& stream)
	{
		while(lastChar!='\n')
		{
			fs>>lastChar;
			if(lastChar!='\n') line+=lastChar;
		}
		if(outputInfo) stream<<std::format("Processed line: \"{}\" is incorrect", line)<<std::endl;	
		line="";
	}
	void Translator::run()
	{
		while(fs.is_open())
		{
			readNext();
		}
	}
}
