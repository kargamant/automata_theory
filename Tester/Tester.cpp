#include "Tester.h"
#include <iostream>

std::vector<std::string> Tester::implimentations={"smc", "regex", "flex"};
std::string Tester::readLine(std::fstream& fs)
{
	char c=0;
	std::string line;

	while(c!='\n' && !fs.eof()) 
	{
		fs>>c;
		if(c!='\n') line+=c;
	}
	return line;
}

std::fstream Tester::openSafe(std::string fileName)
{
	//filename=fileName;
	std::fstream fs(fileName, std::ios::out);
	if(!fs.is_open())
	{
		fs.close();
		fs.open(fileName, std::ios::out);
		fs.close();
		fs.open(fileName);
	}
	//fs.unsetf(fs.skipws);
	return fs;
}

Tester::Tester(std::string filename, std::string basedDir, Generator& gen) : filename(filename), fs(openSafe(filename)), basedDir(basedDir), generator(gen)
{
}

void Tester::writeToPull(int lines)
{
	for(int i=0; i<lines; i++)
	{
		std::string toWrite=generator.genCorrectString();
		fs<<toWrite<<std::endl;
	}
}

void Tester::testAll(int lines)
{
	writeToPull(lines);
	//fs.close();
	for(std::string imp: implimentations)
	{
		std::cout<<imp<<" output:"<<std::endl;
		std::string request="../"+basedDir+"/"+imp+"/main "+filename;
		std::system(request.c_str());
	}
}


