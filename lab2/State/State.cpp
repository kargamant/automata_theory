#include <State.h>

void State::print(std::ostream& stream)
{
    stream<<getFullName()<<std::endl;
}
