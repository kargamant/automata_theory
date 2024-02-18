#include "Translator.h"

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
		std::cout<<"last char: "<<lastChar<<std::endl;
		fsm.readNext();
	}


	void Translator::correct(std::ostream& stream)
	{
		stream<<"Processed line is correct"<<std::endl;
	}
	
	void Translator::incorrect(std::ostream& stream)
	{
		stream<<"Processed line is incorrect"<<std::endl;
	}
	void Translator::run()
	{
		while(fs.is_open())
		{
			readNext();
		}
	}
}
