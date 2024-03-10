#include "SmcRecognizer.h"

int main(int argc, char* argv[])
{
	SmcRecognizer::SmcRecognizer automat;
	if(argc==2)
	{
		if(std::string(argv[1])=="--no-output") 
		{
			automat.run(std::cin, std::cout, true);
		}
		else if(std::string(argv[1])=="--debug")
		{
			automat.setDebugInfo(true);
			automat.run();
		}
		else
		{
			std::fstream fs{argv[1], std::ios::out};
			fs.close();
			fs.open(argv[1]);
			automat.run(std::cin, fs);
		}
	}
	else if(argc==3)
	{
		if(std::string(argv[1])=="--debug")
		{
			automat.setDebugInfo(true);
		}
		std::fstream fs{argv[2], std::ios::out};
		fs.close();
		fs.open(argv[2]);
		automat.run(std::cin, fs);
	}
	else automat.run();
	return 0;
}
