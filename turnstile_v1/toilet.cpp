#include "turnstile.h"

int main()
{
	Turnstile automat;
	automat.dropCoin();
	automat.dropCoin();
	automat.pass();
	automat.pass();
	return 0;
}
