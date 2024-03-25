#include <vector>
#include <string>
#include <fstream>
#include <Generator.h>
#include <iostream>
#include <Recognizer.h>

/*enum class timeMode
{
	correctOnly,
	incorrectOnly,
	all
};*/

class Tester
{
	private:
		std::unordered_map<int, std::vector<int>> table;

		const static std::vector<std::string> implimentations;
		
		int timeImp(Recognizer& rec, const std::vector<std::string>& str_vec);
	public:
		void timing(std::vector<std::string>& str_vec);
		void timingFromTo(std::vector<std::string>& str_vec, int from, int to=0, double relatedStep=0.1);
		void clearTimingData();
		void writeResults();
		void displayResultsTable(std::ostream& stream=std::cout);
};
