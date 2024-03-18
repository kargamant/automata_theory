#include <vector>
#include <string>
#include <fstream>
#include <Generator.h>
#include <iostream>
#include <Recognizer.h>

enum class timeMode
{
	correctOnly,
	incorrectOnly,
	all
};

class Tester
{
	private:
		std::unordered_map<int, std::vector<int>> table;

		static std::vector<std::string> implimentations;
		static std::string incorrectCasesFile;
		static std::string basedDir;
		
		Generator generator;
		std::string readLine(std::fstream& fs);
		std::fstream openSafe(std::string fileName, std::ios_base::openmode mode=std::ios::out);
		int timeImp(Recognizer& rec, const std::vector<std::string>& str_vec);
	public:
		Tester(const Generator& gen) : generator(gen) {}
		
		std::vector<int> timing(std::vector<std::string> str_vec);
		Tester& setGenerator(const Generator& ngen) {generator=ngen; return *this;}
		void clearTimingData();
		void displayResultsTable(std::ostream& stream=std::cout);
};
