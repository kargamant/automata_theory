#include <NFA.h>

namespace Nfa
{
    void NFA::add_state(const std::string& name)
    {
        stateMap.insert({name, std::unordered_map<std::string, std::string>()});
    }

    void NFA::add_transition(const std::string& from, const std::string& to, const std::string& condition)
    {
        stateMap[from].insert({to, condition});
    }


    void NFA::delete_state(const std::string& name)
    {
        stateMap.erase(name);
    }
    void NFA::delete_transition(const std::string& from, const std::string& to)
    {
        stateMap[from].erase(to);
    }

    NFA NFA::plusNFA(NFA& NFA1)
    {
        NFA1.delete_state("start");
        NFA1.delete_state("S0");
        NFA1.delete_state("S1");

        add_state("start");
        add_state("S0");
        add_state("S1");

        add_transition("start", "S0", "");
        //add_transition();
    }
}
