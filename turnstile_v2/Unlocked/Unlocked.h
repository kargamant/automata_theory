#include "../State/State.h"

class Unlocked: public State
{
	private:
		void lock();
		void thanks();
	public:
		Unlocked() {id=StateId::UnlockedId;}

		bool handle(Event event) override;
};
