#include <StateSet.h>
#include <iterator>

int StateSet::LAST_ID=0;

void StateSet::print(std::ostream& stream)
{
    stream<<name<<"_"<<id<<std::endl;
    stream<<"set: {";
    std::copy(set.begin(), set.end(), std::ostream_iterator<std::string>(stream, ", "));
    stream<<"}"<<std::endl;
}
