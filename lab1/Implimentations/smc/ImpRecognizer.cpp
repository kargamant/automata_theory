#include "ImpRecognizer.h"
#include <format>

ImpRecognizer::ImpRecognizer() : fsm(*this) {}
bool ImpRecognizer::checkString(const std::string& str)
{
	for(char c: str)
	{
		lastChar=c;
		fsm.readNext();

		#ifdef DEBUG_INFO
		std::cout<<"last char: "<<lastChar<<" ; current state: "<<fsm.getState().getName()<<std::endl;
		#endif

		if(isStopped || isCorrect) break;
	}
	bool res=isCorrect;
	isCorrect=false;
	isStopped=false;
	zeroWordsRead=true;
	return res;
}
