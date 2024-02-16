#pragma once
#include <unordered_map>
#include <string>

enum class Event
{
	Pass,
	DropCoin
};

enum class StateId
{
	LockedId,
	UnlockedId
};

class State
{
	private:
		void initStateMap();
	protected:
		std::string outSignal;
		StateId id;
	public:	
		State();
		
		std::unordered_map<StateId, std::unordered_map<Event, StateId>> stateMap;
		static State* idToState(StateId id);

		virtual bool handle(Event event)=0;
		StateId getId() {return id;}
};
