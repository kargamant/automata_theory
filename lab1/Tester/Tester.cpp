#include "Tester.h"
#include <filesystem>
#include <iostream> 
#include <chrono>
#include "../Implimentations/flex/ImpRecognizer.h"
#include "../Implimentations/regex/ImpRecognizer.h"
#include "../Implimentations/smc/ImpRecognizer.h"
#include <iterator>

std::vector<std::string> Tester::implimentations={"smc", "flex", "regex"};

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
		std::fstream results{implimentations[i]+"_timing.txt", std::ios::out};
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
	stream<<"	";
	std::copy(implimentations.begin(), implimentations.end(), std::ostream_iterator<std::string>(stream, " "));
	stream<<std::endl;
	for(auto& it: table)
	{
		stream<<it.first<<" ";
		std::copy(it.second.begin(), it.second.end(), std::ostream_iterator<int>(stream, " "));
		stream<<std::endl;
	}
}





