#include <Automat.h>
#include <string>
#include <iostream>
#include <format>

namespace Automato
{
    void Automat::add_state(const std::string& name)
    {
        stateMap.insert({name, std::unordered_map<std::string, std::vector<std::string>>()});
    }

    void Automat::add_transition(const std::string& from, const std::string& to, const std::string& condition)
    {
        if(stateMap[from].contains(to)) stateMap[from][to].push_back(condition);
        else
        {
            stateMap[from].insert({to, {condition}});
        }
    }


    void Automat::delete_state(const std::string& name)
    {
        stateMap.erase(name);
        for(auto& state: stateMap)
        {
            state.second.erase(name);
        }
    }
    void Automat::delete_transition(const std::string& from, const std::string& to, int i)
    {
        stateMap[from][to].erase(stateMap[from][to].begin()+i);
    }

    void Automat::delete_transition(const std::string& from, const std::string& to, const std::string& condition)
    {
        for(int i=0; i<stateMap[from][to].size(); i++)
        {
            if(stateMap[from][to][i]==condition)
            {
                delete_transition(from, to, i);
                break;
            }
        }
    }

    Automat::Automat(Automat& Automat1) : current(Automat1.current), id(Automat1.id), stateMap(Automat1.stateMap)
    {
        //stateMap.merge(Automat1.stateMap);
    }

    Automat::Automat(Automat&& Automat1) :  stateMap(Automat1.stateMap), current(Automat1.current), id(Automat1.id)
    {
        Automat1.current={""};
        Automat1.stateMap.clear();
    }

    Automat::Automat(int id, const std::string& transition) : id(id), current({"start_"+std::to_string(id)})
    {
        add_state("start_"+std::to_string(id));
        add_state("end_"+std::to_string(id));
        add_transition("start_"+std::to_string(id), "end_"+std::to_string(id), transition);
    }

    Automat& Automat::operator<<(Automat& automat)
    {
        if(this!=&automat && automat.id!=id)
        {
            stateMap.merge(automat.stateMap);
        }
        return *this;
    }


    Automat& Automat::operator=(Automat&& automat)
    {
        if(&automat!=this)
        {
            stateMap=automat.stateMap;
            current=automat.current;
            id=automat.id;
        }
        return *this;
    }

    Automat plusAutomat(Automat& Automat1)
    {
        Automat automat{Automat1};
        //considering every Automat have its start and end
        automat.add_transition(Automat1.getEnd(), Automat1.getStart(), "");

        return automat;
    }

    Automat optAutomat(Automat& Automat1)
    {
        Automat automat{Automat1};

        automat.add_transition(Automat1.getStart(), Automat1.getEnd(), "");
        return automat;
    }

    Automat anyAutomat(int id)
    {
        return Automat(id, ".");
    }

    Automat catAutomat(Automat& Automat1, Automat& Automat2)
    {
        Automat automat{Automat1};
        auto stateMap_copy=Automat2.stateMap;
        automat<<Automat2;
        Automat2.stateMap=stateMap_copy;
        automat.id=Automat1.id+Automat2.id;
        automat.add_state(automat.getStart());
        automat.add_state(automat.getEnd());

        automat.add_transition(automat.getStart(), Automat1.getStart(), "");
        automat.add_transition(Automat2.getEnd(), automat.getEnd(), "");

        automat.add_transition(Automat1.getEnd(), Automat2.getStart(), "");

        return automat;
    }

    Automat orAutomat(Automat& Automat1, Automat& Automat2)
    {
        Automat automat{Automat1};
        auto stateMap_copy=Automat2.stateMap;
        automat<<Automat2;
        Automat2.stateMap=stateMap_copy;
        automat.id=Automat1.id+Automat2.id;
        automat.add_state(automat.getStart());
        automat.add_state(automat.getEnd());

        automat.add_transition(automat.getStart(), Automat1.getStart(), "");
        automat.add_transition(automat.getStart(), Automat2.getStart(), "");

        automat.add_transition(Automat1.getEnd(), automat.getEnd(), "");
        automat.add_transition(Automat2.getEnd(), automat.getEnd(), "");
        return automat;
    }

    void Automat::printAutomat(std::ostream& stream)
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
                for(auto& condition: transition.second)
                {
                    stream<<std::format("(\"{}\", \"{}\")", transition.first, condition)<<" ;";
                }
            }
            stream<<std::endl;
        }
        stream<<std::endl;
    }

    void Automat::printDot(std::ostream& stream)
    {
        stream<<"digraph"<<std::endl<<"{"<<std::endl;
        for(auto& state: stateMap)
        {
            for(auto& transition: state.second)
            {
                for(auto& condition: transition.second)
                {
                    if(condition!="") stream<<state.first<<"->"<<transition.first<<" [label="<<condition<<"]"<<std::endl;
                    else stream<<state.first<<"->"<<transition.first<<" [label=ε]"<<std::endl;
                }
            }
        }
        stream<<"}"<<std::endl;
    }
}


