#pragma once
#include <string>
#include <iostream>

struct State
{
    std::string name;
    bool isStarting;
    bool isAccepting;
    //State(std::string name="boba") : name(name), isStarting(false), isAccepting(false) {}
    State(const std::string& name="boba") : name(name), isStarting(false), isAccepting(false) {}
    //std::string getFullName() {return name+"_"+std::to_string(id);}
    void print(std::ostream& stream=std::cout);
};
