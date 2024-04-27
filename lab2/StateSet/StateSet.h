#include <set>
#include <string>
#include <iostream>
#include <State.h>

struct StateSet
{
    static int LAST_ID;
    std::set<std::string> set;
    std::string name;
    int id;
    StateSet(std::set<std::string>& set, std::string name="StateSet") : set(set), name(name), id(LAST_ID+1) { LAST_ID++;}
    StateSet(std::string& state, std::string name="StateSet") : set({state}), name(name), id(LAST_ID+1) { LAST_ID++;}
    void print(std::ostream& stream=std::cout);
    std::string getFullName() {return name+std::to_string(id);}
};
