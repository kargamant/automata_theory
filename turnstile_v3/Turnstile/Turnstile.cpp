#include "Turnstile.h"
#include <iostream>

namespace turnstile
{
	void Turnstile::unlock()
	{
		std::cout<<"unlocked!"<<std::endl;
	}
	
	void Turnstile::lock()
	{
		std::cout<<"locked!"<<std::endl;
	}

	void Turnstile::alarm()
	{
		std::cout<<"Alarm! Get out of here frauder."<<std::endl;
	}

	void Turnstile::thanks()
	{
		std::cout<<"Thank you for supporting me!"<<std::endl;
	}
}
