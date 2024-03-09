#include "Translator.h"

int main(int argc, char* argv[])
{
	/*if(argc==1) throw std::invalid_argument("Error. No file specified");
	std::string fileName=argv[1];
	Translator::Translator automat(fileName);
	if(argc==3)
	{
		if(std::string(argv[2])=="--no-output")
		{
			automat.setOutputInfo(false);
		}
		else if(std::string(argv[2])=="--debug")
		{
			automat.setDebugInfo(true);
		}
	}*/
	Translator::Translator automat;
	//std::fstream fs("file_f.txt", std::ios::in);
	//fs.unsetf(fs.skipws);
	automat.run(std::cin, std::cout);
	return 0;
}
