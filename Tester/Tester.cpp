#include "Tester.h"
#include <iostream>
#include <chrono>

std::vector<std::string> Tester::implimentations={"smc", "regex", "flex"};
std::string Tester::incorrectCasesFile="incorrect_cases.txt";
std::string Tester::basedDir="Implimentations";
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

std::fstream Tester::openSafe(std::string fileName, std::ios_base::openmode mode)
{
	//filename=fileName;
	std::fstream fs(fileName, mode);
	if(!fs.is_open())
	{
		fs.close();
		fs.open(fileName, mode);
		fs.close();
		fs.open(fileName);
	}
	fs.unsetf(fs.skipws);
	return fs;
}

/*Tester::Tester(std::string filename, std::string basedDir, Generator& gen) : filename(filename), fs(openSafe(filename)), basedDir(basedDir), generator(gen)
{
}*/

/*void Tester::writeToPull(int lines)
{
	std::fstream load=openSafe("../Tester/"+incorrectCasesFile, std::ios::in);
	std::vector<std::string> cases;
	while(!load.eof())
	{
		cases.push_back(readLine(load));
	}
	for(int i=0; i<lines; i++)
	{
		int choice=generator.genChoice();
		std::string toWrite;
		if(choice) 
		{
			toWrite=generator.genCorrectString();
		}
		else
		{
			toWrite=generator.genIncorrectString(cases);
		}
		fs<<toWrite<<std::endl;
	}
}*/

/*void Tester::testAll(int lines)
{
	writeToPull(lines);
	//fs.close();
	for(std::string imp: implimentations)
	{
		std::cout<<std::endl<<imp<<" output:"<<std::endl;
		std::string request;
		if(imp!="regex") request="../"+basedDir+"/"+imp+"/main "+filename;
		else request="../"+basedDir+"/"+imp+"/main "+"../"+basedDir+"/"+imp+"/regexp.txt "+filename;
		std::system(request.c_str());
	}
}*/

void Tester::timing(int lines)
{
	//writeToPull(lines);
	std::vector<int> resVec;
	std::string genRequest="(cd ../Generator ; ./gen "+std::to_string(lines)+")";
	for(std::string imp: implimentations)
	{
		std::fstream results=openSafe(imp+"_timing.txt", std::ios::app);
		std::string request=genRequest+" | "+"../"+basedDir+"/"+imp+"/main --no-output";
		//if(imp=="flex") request=genRequest+"| "+"../"+basedDir+"/"+imp+"/main --no-output";
		//else if(imp=="regex") request="../"+basedDir+"/"+imp+"/main "+"../"+basedDir+"/"+imp+"/regexp.txt "+filename+" --no-output";
		//else request="../"+basedDir+"/"+imp+"/main "+filename+" --no-output";
		auto start=std::chrono::system_clock::now();
		std::system(request.c_str());
		auto end=std::chrono::system_clock::now();
		auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
		results<<std::to_string(lines)+" "+std::to_string(duration.count())<<std::endl;
		resVec.push_back(duration.count());
	}
	table.insert({lines, resVec});
}


void Tester::clearTimingData()
{
	for(std::string imp: implimentations)
	{
		std::fstream results=openSafe(imp+"_timing.txt", std::ios::out);
		results.close();
	}
}


void Tester::displayResultsTable(std::ostream& stream)
{
	stream<<"     ";
	for(std::string imp: implimentations)
	{
		stream<<imp<<" ";
	}
	stream<<std::endl;
	for(auto it: table)
	{
		stream<<it.first<<" ";
		for(auto res: it.second)
		{
			stream<<res<<" ";
		}
		stream<<std::endl;
	}
}





