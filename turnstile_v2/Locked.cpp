#include "Locked.h"
#include <iostream>


void Locked::alarm()
{
	outSignal="Alarm! Go out frauder.";
	std::cout<<outSignal<<std::endl;
}

void Locked::unlock()
{
	outSignal="unlocked";
	std::cout<<outSignal<<std::endl;
}

bool Locked::handle(Event event)
{
	if(event==Event::Pass)
	{
		alarm();
		return false; //dont need to change current state
	}
	else if(event==Event::DropCoin)
	{
		unlock();
		return true; //need to transit to unlocked state
	}
}
