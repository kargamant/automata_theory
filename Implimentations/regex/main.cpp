#include "RegexRecognizer.h"
#include <fstream>
#include <iostream>

int main(int argc, char* argv[])
{
	std::string reg="for\\s+([a-zA-Z][\\w]+|[a-zA-Z])\\s+in\\s+\\(\\s*(((([a-zA-Z][\\w]+|[a-zA-Z])|'([^']+|)'|\"([^\"]+|)\"|[0-9]+)\\s+(([a-zA-Z][\\w]+|[a-zA-Z])|'([^']+|)'|\"([^\"]+|)\"|[0-9]+|\\s*)*)|(([a-zA-Z][\\w]+|[a-zA-Z])|'([^']+|)'|\"([^\"]+|)\"|[0-9]+))\\)";
	RegexRecognizer rec{reg};
	if(argc==2)
	{
		if(std::string(argv[1])=="--no-output") 
		{
			rec.run(std::cin, std::cout, true);
		}
		else
		{
			std::fstream fs{argv[1], std::ios::out};
			fs.close();
			fs.open(argv[1]);
			rec.run(std::cin, fs);
		}
	}
	else rec.run();
	
	return 0;
}
