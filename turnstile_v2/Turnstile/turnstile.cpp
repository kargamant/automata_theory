#include "turnstile.h"

void Turnstile::pass()
{
	if(state->handle(Event::Pass))
	{
		transit(Event::Pass);
	}
}

void Turnstile::dropCoin()
{
	if(state->handle(Event::DropCoin))
	{
		transit(Event::DropCoin);
	}
}

void Turnstile::transit(Event event)
{
	State* newState=State::idToState(state->stateMap[state->getId()][event]);
	delete state;
	state=newState;
}
