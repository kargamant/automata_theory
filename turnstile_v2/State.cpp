#include "State.h"
#include "Locked.h"
#include "Unlocked.h"

State* State::idToState(StateId id)
{
	switch(id)
	{
		case StateId::LockedId:
			return new Locked();
		case StateId::UnlockedId:
			return new Unlocked();
		default:
			return nullptr;
	}
}

void State::initStateMap()
{
	stateMap.insert({StateId::LockedId, std::unordered_map<Event, StateId>()});
	stateMap.insert({StateId::UnlockedId, std::unordered_map<Event, StateId>()});

	stateMap[StateId::LockedId].insert({Event::Pass, StateId::LockedId});
	stateMap[StateId::LockedId].insert({Event::DropCoin, StateId::UnlockedId});

	stateMap[StateId::UnlockedId].insert({Event::Pass, StateId::LockedId});
	stateMap[StateId::UnlockedId].insert({Event::DropCoin, StateId::UnlockedId});
}

State::State() : id(), outSignal()
{
	initStateMap();
}
