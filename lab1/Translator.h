#include "automat_sm.h"
#include <string>
#include <iostream>
#include <fstream>

namespace Translator
{
	class Translator  
	{
		private:
			char lastChar;
			std::string line;
			std::fstream fs;
			automatContext fsm;
		public:
			Translator();
			Translator(std::string& fileName); 
			
			//friend automatContext;
			void readNext();
			char lastRead() {return lastChar;}
			void correct(std::ostream& stream=std::cout);
			void incorrect(std::ostream& stream=std::cout);
			void shutDown() {fs.close();}
			void run();
			bool isValidRead() {return (lastChar>=97 && lastChar<=122) || (lastChar>=65 && lastChar<=90) || isNumber();}
			bool isNumber() {return (lastChar>=48 && lastChar<=57);}
	};
}
