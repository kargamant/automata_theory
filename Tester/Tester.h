#include <vector>
#include <string>
#include <fstream>
#include "../Generator/Generator.h"
#include <iostream>

class Tester
{
	private:
		std::unordered_map<int, std::vector<int>> table;
		static std::vector<std::string> implimentations;
		static std::string incorrectCasesFile;
		std::string basedDir;
		std::fstream fs;
		std::string filename;
		Generator generator;
		std::string readLine(std::fstream& fs);
		std::fstream openSafe(std::string fileName, std::ios_base::openmode mode=std::ios::out);
		void writeToPull(int lines);
	public:
		Tester(std::string filename, std::string basedDir, Generator& gen);
		void testAll(int lines=1);
		void timing(int lines=1);
		Tester& setGenerator(Generator& ngen) {generator=ngen; return *this;}
		void clearTimingData();
		void displayResultsTable(std::ostream& stream=std::cout);
};