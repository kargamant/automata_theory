#include <Transition.h>
#include <format>


void Transition::print(std::ostream& stream)
{
    stream<<std::format("{}-{}->{}", from.getFullName(), tr, to.getFullName())<<std::endl;
}
