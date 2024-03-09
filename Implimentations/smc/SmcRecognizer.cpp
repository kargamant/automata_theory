#include "SmcRecognizer.h"
#include <format>

namespace SmcRecognizer
{

	SmcRecognizer::SmcRecognizer() : fsm(*this) //, fs("file.txt") 
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

	/*SmcRecognizer::SmcRecognizer(std::string& fileName) : fsm(*this), fs(std::fstream())
	{
		fs.open(fileName, std::ios::in);
		fs.unsetf(fs.skipws);
	}*/

	void SmcRecognizer::correct(std::ostream& stream)
	{
		isCorrect=true;
	}
	
	void SmcRecognizer::incorrect(std::ostream& stream)
	{
		isCorrect=false;
	}
	/*void SmcRecognizer::run(std::istream& in, std::ostream& out)
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
	}*/
	bool SmcRecognizer::checkString(std::string& str)
	{
		for(char c: str)
		{
			lastChar=c;
			fsm.readNext();
			if(debugInfo) std::cout<<"last char: "<<lastChar<<" ; current state: "<<fsm.getState().getName()<<std::endl;
			if(isStopped || isCorrect) break;
		}
		bool res=isCorrect;
		isCorrect=false;
		isStopped=false;
		return res;
	}
}
