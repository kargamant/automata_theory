#include <string>

enum class State
{
	Locked,
	Unlocked
};

enum class Event
{
	Pass,
	DropCoin
};

class Turnstile
{
private:
	State state=State::Locked;

	//transition func
	void transit(Event event);
	
	//exit signals
	void unlock();
	void lock();
	void alarm();
	void thanks();
public:
	//entering signals
	void pass();
	void dropCoin();

};
