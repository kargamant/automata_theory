#include <State.h>

void State::print(std::ostream& stream)
{
    stream<<getFullName()<<std::endl;
}

std::string stateTypeToString(StateType type)
{
    switch(type)
    {
        case StateType::Start:
            return "start";
        case StateType::End:
            return "end";
        case StateType::Basic:
            return "basic";
    }
}
