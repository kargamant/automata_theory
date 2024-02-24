#include "Translator.h"

int main(int argc, char* argv[])
{
	if(argc==1) throw std::invalid_argument("Error. No file specified");
	std::string fileName=argv[1];
	Translator::Translator automat(fileName);
	automat.run();
	return 0;
}
