#include "Translator.h"

int main()
{
	std::string fileName="input.txt";
	Translator::Translator automat(fileName);
	automat.run();
	return 0;
}
