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
		else
		{
			std::fstream fs{argv[1], std::ios::out};
			fs.close();
			fs.open(argv[1]);
			automat.run(std::cin, fs);
		}
	}
	else automat.run();
	return 0;
}
