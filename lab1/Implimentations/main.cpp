#include <ImpRecognizer.h>
#include <iostream>

#ifdef FLEX 
using namespace Flex;
#elif defined SMC
using namespace Smc;
#elif defined REGEX
using namespace Regex;
#endif

void run(std::istream& in, std::ostream& out, Recognizer& rec, bool noOutput=true)
{
	char c;
	std::string line;
	in.unsetf(in.skipws);
	while(!in.eof())
	{
		while(c!='\n')
		{
			in>>c;
			if(in.eof()) 
			{
				break;
			}
			line+=c;
		}
		if(in.eof()) break;
		bool result=rec.checkString(line);
		line.pop_back();
		if(!noOutput) out<<line<<": "<<result<<std::endl;
		line="";
		c=0;
	}
}

int main()
{
	ImpRecognizer rec=ImpRecognizer();
	run(std::cin, std::cout, rec, false);
	return 0;
}
