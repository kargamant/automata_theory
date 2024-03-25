#include "automat_sm.h"
#include <string>
#include <iostream>
#include <fstream>
#include <Recognizer.h>

namespace Smc
{
	class ImpRecognizer : public Recognizer
	{
		private:
			char lastChar;
			bool isCorrect=false;
			bool isStopped=false;
			bool zeroWordsRead=true;
			automatContext fsm;

		public:
			ImpRecognizer() : fsm(*this) {}
			bool checkString(const std::string& str) override;
	
			char lastRead() {return lastChar;}
			void correct() {isCorrect=true;}
			void incorrect() {isCorrect=false;}
			bool isValidRead() {return (lastChar>=97 && lastChar<=122) || (lastChar>=65 && lastChar<=90) || isNumber();}
			bool isNumber() {return (lastChar>=48 && lastChar<=57);}
	
			ImpRecognizer& setStopped(bool nstop) {isStopped=nstop; return *this;}
			ImpRecognizer& setZeroWordsRead(bool nzero) {zeroWordsRead=nzero; return *this;}
			bool getZeroWordsRead() {return zeroWordsRead; }
	};
}
