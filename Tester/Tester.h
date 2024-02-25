#include <vector>
#include <string>
#include <fstream>
#include "../Generator/Generator.h"

class Tester
{
	private:
		static std::vector<std::string> implimentations;
		std::string basedDir;
		std::fstream fs;
		std::string filename;
		Generator generator;
		std::string readLine(std::fstream& fs);
		std::fstream openSafe(std::string fileName);
		void writeToPull(int lines);
	public:
		Tester(std::string filename, std::string basedDir, Generator& gen);
		void testAll(int lines=1);
		Tester& setGenerator(Generator& ngen) {generator=ngen; return *this;}
};
