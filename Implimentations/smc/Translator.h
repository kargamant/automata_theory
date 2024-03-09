#include "automat_sm.h"
#include <string>
#include <iostream>
#include <fstream>
#include "../../Recognizer/Recognizer.h"

namespace Translator
{
	class Translator : public Recognizer
	{
		private:
			bool isCorrect=false;
			bool isStopped=false;
			bool debugInfo=false;
			//bool outputInfo=true;
			char lastChar;
			std::string line;
			//std::fstream fs;
			automatContext fsm;
		public:
			Translator();
			//Translator(std::string& fileName); 
			
			bool checkString(std::string& str) override;

			//friend automatContext;
			//void readNext();
			char lastRead() {return lastChar;}
			void correct(std::ostream& stream=std::cout);
			void incorrect(std::ostream& stream=std::cout);
			//void shutDown() {fs.close();}
			void run(std::istream& in, std::ostream& out);
			bool isValidRead() {return (lastChar>=97 && lastChar<=122) || (lastChar>=65 && lastChar<=90) || isNumber();}
			bool isNumber() {return (lastChar>=48 && lastChar<=57);}

			Translator& setDebugInfo(bool ndebugInfo) {debugInfo=ndebugInfo; return *this;}
			//Translator& setOutputInfo(bool noutputInfo) {outputInfo=noutputInfo; return *this;}
			Translator& setStopped(bool nstop) {isStopped=nstop; return *this;}
			//std::fstream& getFs() {return fs;}
	};
}
