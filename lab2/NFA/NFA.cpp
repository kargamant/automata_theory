#include <NFA.h>
#include <string>
#include <iostream>
#include <format>

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


    NFA::NFA(NFA& NFA1) : current(NFA1.current), id(NFA1.id), stateMap(NFA1.stateMap)
    {
        //stateMap.merge(NFA1.stateMap);
    }

    NFA::NFA(NFA&& NFA1) :  stateMap(NFA1.stateMap), current(NFA1.current), id(NFA1.id)
    {
        NFA1.current={""};
        NFA1.stateMap.clear();
    }

    NFA::NFA(int id, const std::string& transition) : id(id), current({"start_"+std::to_string(id)})
    {
        add_state("start_"+std::to_string(id));
        add_state("end_"+std::to_string(id));
        add_transition("start_"+std::to_string(id), "end_"+std::to_string(id), transition);
    }

    NFA& NFA::operator<<(NFA& nfa)
    {
        if(this!=&nfa && nfa.id!=id)
        {
            stateMap.merge(nfa.stateMap);
        }
        return *this;
    }



    NFA plusNFA(NFA& NFA1)
    {
        NFA nfa{NFA1};
        //considering every NFA have its start and end
        nfa.add_transition(NFA1.getEnd(), NFA1.getStart(), "");

        return nfa;
    }

    NFA optNFA(NFA& NFA1)
    {
        NFA nfa{NFA1};

        nfa.add_transition(NFA1.getStart(), NFA1.getEnd(), "");
        return nfa;
    }

    NFA anyNFA(int id)
    {
        return NFA(id, ".");
    }

    NFA catNFA(NFA& NFA1, NFA& NFA2)
    {
        NFA nfa{NFA1};
        auto stateMap_copy=NFA2.stateMap;
        nfa<<NFA2;
        NFA2.stateMap=stateMap_copy;
        nfa.id=NFA1.id+NFA2.id;
        nfa.add_state(nfa.getStart());
        nfa.add_state(nfa.getEnd());

        nfa.add_transition(nfa.getStart(), NFA1.getStart(), "");
        nfa.add_transition(NFA2.getEnd(), nfa.getEnd(), "");

        nfa.add_transition(NFA1.getEnd(), NFA2.getStart(), "");

        return nfa;
    }

    NFA orNFA(NFA& NFA1, NFA& NFA2)
    {
        NFA nfa{NFA1};
        auto stateMap_copy=NFA2.stateMap;
        nfa<<NFA2;
        NFA2.stateMap=stateMap_copy;
        nfa.id=NFA1.id+NFA2.id;
        nfa.add_state(nfa.getStart());
        nfa.add_state(nfa.getEnd());

        nfa.add_transition(nfa.getStart(), NFA1.getStart(), "");
        nfa.add_transition(nfa.getStart(), NFA2.getStart(), "");

        nfa.add_transition(NFA1.getEnd(), nfa.getEnd(), "");
        nfa.add_transition(NFA2.getEnd(), nfa.getEnd(), "");
        return nfa;
    }

    void NFA::printNfa(std::ostream& stream)
    {
        stream<<"current_state_set:"<<std::endl;
        std::copy(current.begin(), current.end(), std::ostream_iterator<std::string>(stream, " "));
        stream<<std::endl;

        stream<<"defined transitions:"<<std::endl;
        for(auto& state: stateMap)
        {
            stream<<state.first<<" | ";
            for(auto& transition: state.second)
            {
                stream<<std::format("(\"{}\", \"{}\")", transition.first, transition.second)<<" ;";
            }
            stream<<std::endl;
        }
        stream<<std::endl;
    }

}



