#include <iostream>
#include <vector>

class Robo
{
	private:
		std::pair<int, int> coordinates;
		int angle; //Can only be 30, 90, 150, 210, 270 or 330
	public:
		Robo(int x=0, int y=0, int angle=30);
		void rl();
		void rr();
		void go();
		std::vector<std::pair<int, int>> sonar();

		std::pair<int, int> next_coordinates();
		std::pair<int, int> getCoordinates() {return coordinates;}
		int getX() {return coordinates.first;}
		int getY() {return coordinates.second;}

		friend void operator<<(std::ostream& stream, Robo& robo);
};
