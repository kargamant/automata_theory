#include "../gen/turnstile_sm.h"

namespace turnstile
{
class Turnstile
{
	public:
		turnstileContext _fsm;
		Turnstile() : _fsm(*this) {}
		void unlock();
		void lock();
		void alarm();
		void thanks();
};
}
