#include <State.h>

void State::print(std::ostream& stream)
{
    stream<<name<<std::endl;
    stream<<"isStarting: "<<isStarting<<std::endl;
    stream<<"isAccepting: "<<isAccepting<<std::endl;

}
