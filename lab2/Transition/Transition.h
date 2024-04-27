#pragma once

#include <string>
#include <State.h>
#include <iostream>

struct Transition
{
    State from;
    State to;
    std::string tr;
    Transition(State& from, State& to, std::string& tr) : from(from), to(to), tr(tr) {}
    void print(std::ostream& stream=std::cout);
};
