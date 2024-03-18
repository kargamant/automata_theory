#include "Tester.h"
#include <iostream> 
#include <chrono>
#include "../Implimentations/flex/ImpRecognizer.h"
#include "../Implimentations/regex/ImpRecognizer.h"
#include "../Implimentations/smc/ImpRecognizer.h"

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

std::vector<int> Tester::timing(std::vector<std::string> str_vec)
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
	return resVec;
	/*std::string genRequest="(cd ../Generator ; ./gen "+std::to_string(lines);
	if(mode==timeMode::correctOnly) genRequest+=" --correct )";
	else if(mode==timeMode::incorrectOnly) genRequest+=" --incorrect )";
	else genRequest+=" )";
	for(const auto& imp: implimentations)
	{
		std::fstream results=openSafe(imp+"_timing.txt", std::ios::app);
		std::string request=genRequest+" | "+"../"+basedDir+"/"+imp+"/main --no-output";

		auto start=std::chrono::system_clock::now();
		std::system(request.c_str());
		auto end=std::chrono::system_clock::now();
		auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
		
		results<<lines<<" "<<duration.count()<<std::endl;
		resVec.push_back(duration.count());
	}*/
	//table.emplace(lines, std::move(resVec));
}


void Tester::clearTimingData()
{
	for(std::string imp: implimentations)
	{
		//std::filesystem remove
		std::fstream results=openSafe(imp+"_timing.txt", std::ios::out);
		results.close();
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





