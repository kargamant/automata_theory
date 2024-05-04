#pragma once
#include <string>
#include <iostream>

enum class StateType
{
    Start,
    End,
    Basic
};

std::string stateTypeToString(StateType type);

struct State
{
    StateType type;
    int id;
    State(StateType type=StateType::Basic, int id=-1) : type(type), id(id) {}
    std::string getFullName() {return stateTypeToString(type)+"_"+std::to_string(id);}
    void print(std::ostream& stream=std::cout);
};
