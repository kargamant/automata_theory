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
