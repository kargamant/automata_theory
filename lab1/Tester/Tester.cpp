#include "Tester.h"
#include <filesystem>
#include <iostream> 
#include <chrono>
#include "../Implimentations/flex/ImpRecognizer.h"
#include "../Implimentations/regex/ImpRecognizer.h"
#include "../Implimentations/smc/ImpRecognizer.h"

std::vector<std::string> Tester::implimentations={"smc", "flex", "regex"};

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


int Tester::timeImp(Recognizer& rec, const std::vector<std::string>& str_vec)
{
	auto start=std::chrono::system_clock::now();
	for(auto& str: str_vec)
	{
		rec.checkString(str);
	}
	auto end=std::chrono::system_clock::now();
	auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
	return duration;
}

void Tester::timing(std::vector<std::string>& str_vec)
{
	std::vector<int> resVec;
	Recognizer* smc=new Smc::ImpRecognizer();
	Recognizer* flex=new Flex::ImpRecognizer();
	Recognizer* regex=new Regex::ImpRecognizer();
	
	resVec.push_back(timeImp(*smc, str_vec));
	resVec.push_back(timeImp(*flex, str_vec));
	resVec.push_back(timeImp(*regex, str_vec));
	delete smc;
	delete flex;
	delete regex;
	table.emplace(str_vec.size(), std::move(resVec));
}

void Tester::timingFromTo(std::vector<std::string>& str_vec, int from, int to, double relatedStep)
{
	int max_lines=from;
	while(from!=to)
	{
		timing(str_vec);
		from-=relatedStep*max_lines;
		str_vec.resize(from);
	}
}

void Tester::writeResults()
{
	for(int i=0; i<implimentations.size(); i++)
	{
		std::fstream results=openSafe(implimentations[i]+"_timing.txt", std::ios::app);
		for(auto& it: table)
		{
			results<<it.first<<" "<<it.second[i]<<std::endl;
		}
	}
}

void Tester::clearTimingData()
{
	table.clear();
	for(auto& imp: implimentations)
	{
		std::filesystem::remove(imp+"_timing.txt");
	}
}

//реализовать с помощью std::ostream_iterator и std::copy
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





