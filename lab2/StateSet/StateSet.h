#include <unordered_set>
#include <string>
#include <iostream>
#include <State.h>

struct StateSet
{
    static int LAST_ID;
    std::unordered_set<int> set;
    int id;
    StateSet(std::unordered_set<int>& set) : set(set), id(LAST_ID+1) { LAST_ID++;}
    StateSet(int state) : set({state}), id(LAST_ID+1) { LAST_ID++;}
    StateSet() : set(), id(LAST_ID+1) {LAST_ID++;}
    void print(std::ostream& stream=std::cout) const;

    bool operator<(const StateSet& set2) const {return id<set2.id;}
    //std::string getFullName() const {return name+std::to_string(id);}
};
