#include <string>
#include "../State/State.h"
#include "../Locked/Locked.h"

class Turnstile
{
private:
	State* state=nullptr;
	
	
	//transition func
	void transit(Event event);	
public:
	Turnstile() : state(new Locked()) {}

	//entering signals
	void pass();
	void dropCoin();

};
