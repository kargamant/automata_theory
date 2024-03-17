#include "automat_sm.h"
#include <string>
#include <iostream>
#include <fstream>
#include <Recognizer.h>

class ImpRecognizer : public Recognizer
{
	private:
		bool isCorrect=false;
		bool isStopped=false;
		bool debugInfo=false;
		bool zeroWordsRead=true;
		automatContext fsm;
	public:
		ImpRecognizer();
		
		bool checkString(std::string& str) override;

		void correct(std::ostream& stream=std::cout);
		void incorrect(std::ostream& stream=std::cout);
		bool isValidRead() {return (lastChar>=97 && lastChar<=122) || (lastChar>=65 && lastChar<=90) || isNumber();}
		bool isNumber() {return (lastChar>=48 && lastChar<=57);}

		ImpRecognizer& setDebugInfo(bool ndebugInfo) {debugInfo=ndebugInfo; return *this;}
		ImpRecognizer& setStopped(bool nstop) {isStopped=nstop; return *this;}
		ImpRecognizer& setZeroWordsRead(bool nzero) {zeroWordsRead=nzero; return *this;}
		bool getZeroWordsRead() {return zeroWordsRead; }
};
