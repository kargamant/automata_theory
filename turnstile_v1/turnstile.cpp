#include "turnstile.h"
#include <iostream>

void Turnstile::pass()
{
	transit(Event::Pass);
}

void Turnstile::dropCoin()
{
	transit(Event::DropCoin);
}

void Turnstile::unlock()
{
	state=State::Unlocked;
	std::cout<<"unlocked"<<std::endl;
}

void Turnstile::lock()
{
	state=State::Locked;
	std::cout<<"locked"<<std::endl;
}

void Turnstile::alarm()
{
	std::cout<<"Alarm! Go out frauder."<<std::endl;
}
void Turnstile::thanks()
{
	std::cout<<"Thank you very much for supporting me!"<<std::endl;
}

void Turnstile::transit(Event event)
{
	if(event==Event::Pass)
	{
		if(state==State::Locked)
		{
			alarm();
		}
		else
		{
			lock();
		}
	}
	else if(event==Event::DropCoin)
	{
		if(state==State::Locked)
		{
			unlock();
		}
		else
		{
			thanks();
		}
	}
}
