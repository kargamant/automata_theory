#include "SmcRecognizer.h"
#include <format>

namespace SmcRecognizer
{

	SmcRecognizer::SmcRecognizer() : fsm(*this)  
	{
	}

	void SmcRecognizer::correct(std::ostream& stream)
	{
		isCorrect=true;
	}
	
	void SmcRecognizer::incorrect(std::ostream& stream)
	{
		isCorrect=false;
	}

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
