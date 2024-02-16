#include <string>
#include "State.h"
#include "Locked.h"

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
