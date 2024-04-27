#pragma once
#include <string>
#include <iostream>

struct State
{
    std::string name;
    int id;
    State(const std::string& name, int id) : name(name), id(id) {}
    std::string getFullName() {return name+"_"+std::to_string(id);}
    void print(std::ostream& stream=std::cout);
};
