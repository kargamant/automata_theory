#include "turnstile.h"

int main()
{
	Turnstile automat;
	automat.pass();
	automat.dropCoin();
	automat.pass();
	automat.dropCoin();
	automat.dropCoin();
	automat.dropCoin();
	automat.pass();
	automat.pass();
	automat.pass();
	return 0;
}
