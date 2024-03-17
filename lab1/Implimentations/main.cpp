#include <ImpRecognizer.h>
#include <iostream>

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
	Recognizer* rec=new ImpRecognizer();
	run(std::cin, std::cout, *rec, false);	
	delete rec;
	return 0;
}
