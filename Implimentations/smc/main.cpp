#include "SmcRecognizer.h"

int main(int argc, char* argv[])
{
	/*if(argc==1) throw std::invalid_argument("Error. No file specified");
	std::string fileName=argv[1];
	SmcRecognizer::SmcRecognizer automat(fileName);
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
	SmcRecognizer::SmcRecognizer automat;
	if(argc==2) 
	{
		std::fstream fs{argv[1], std::ios::out};
		fs.close();
		fs.open(argv[1]);
		automat.run(std::cin, fs);
	}
	else automat.run(std::cin, std::cout);
	return 0;
}
