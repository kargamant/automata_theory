#include "ImpRecognizer.h"
#include <format>


ImpRecognizer::ImpRecognizer() : fsm(*this)  
{
}

void ImpRecognizer::correct(std::ostream& stream)
{
	isCorrect=true;
}

void ImpRecognizer::incorrect(std::ostream& stream)
{
	isCorrect=false;
}

bool ImpRecognizer::checkString(std::string& str)
{
	std::cout<<"Hey. I am smc!"<<std::endl;
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
	zeroWordsRead=true;
	return res;
}
