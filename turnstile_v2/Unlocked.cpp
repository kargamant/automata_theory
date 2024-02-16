#include "Unlocked.h"
#include <iostream>


void Unlocked::lock()
{
	outSignal="locked";
	std::cout<<outSignal<<std::endl;
}

void Unlocked::thanks()
{
	outSignal="Thank you very much for supporting me!";
	std::cout<<outSignal<<std::endl;
}

bool Unlocked::handle(Event event)
{
	if(event==Event::Pass)
	{
		lock();
		return true;
	}
	else if(event==Event::DropCoin)
	{
		thanks();
		return false;
	}
}
