#include "Robo.h"

Robo::Robo(int x, int y, int angle) : coordinates({x, y}), angle(angle)
{
	if(angle%30!=0) throw std::invalid_argument("Error. Cant set angle that is not 30, 90, 150, 210, 270 or 330");
	else if(angle>330) angle/=360;
}

void operator<<(std::ostream& stream, Robo& robo)
{
	switch(robo.angle)
	{
		case 30:
			stream<<"/'";
			break;
		case 90:
			stream<<"^";
			break;
		case 150:
			stream<<"'\\";
			break;
		case 210:
			stream<<",/";
			break;
		case 270:
			stream<<"v";
			break;
		case 330:
			stream<<"\\,";
			break;
	}
}

void Robo::rl()
{
	angle+=60;
	if(angle>360) angle-=360;
}
void Robo::rr()
{
	angle-=60;
	if(angle<0) angle+=360;
}

std::pair<int, int> Robo::next_coordinates()
{
	std::pair<int, int> ncoordinates=coordinates;
	if(coordinates.second%2==0)
	{
		switch(angle)
		{
			case 30:
				ncoordinates.second++;
				break;
			case 90:
				ncoordinates.first--;
				break;
			case 150:
				ncoordinates.second--;
				break;
			case 210:
				ncoordinates.first++;
				ncoordinates.second--;
				break;
			case 270:
				ncoordinates.first++;
				break;
			case 330:
				ncoordinates.first++;
				ncoordinates.second++;
				break;
		}
	}
	else
	{
		switch(angle)
		{
			case 30:
				ncoordinates.first--;
				ncoordinates.second++;
				break;
			case 90:
				ncoordinates.first--;
				break;
			case 150:
				ncoordinates.first--;
				ncoordinates.second--;
				break;
			case 210:
				ncoordinates.second--;
				break;
			case 270:
				ncoordinates.first++;
				break;
			case 330:
				ncoordinates.second++;
				break;
		}
	}
	return ncoordinates;
}

void Robo::go()
{
	coordinates=next_coordinates();
}

std::vector<std::pair<int, int>> Robo::sonar()
{
	std::vector<std::pair<int, int>> result;
	int old_angle=angle;
	result.push_back(next_coordinates());
	rl();
	while(angle!=old_angle)
	{
		if(angle!=(old_angle+180)%360) result.push_back(next_coordinates());
		rl();
	}
	return result;
}
















