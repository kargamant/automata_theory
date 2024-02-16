#include "State.h"

class Locked: public State
{
	private:

		void alarm();
		void unlock();
	public:
		Locked() {id=StateId::LockedId;}

		bool handle(Event event) override;
};
