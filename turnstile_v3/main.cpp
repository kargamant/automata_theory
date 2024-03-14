#include "Turnstile/Turnstile.h"

int main()
{
	turnstile::Turnstile automat;
	automat._fsm.pass();
	automat._fsm.dropCoin();
	automat._fsm.pass();

	return 0;
}
