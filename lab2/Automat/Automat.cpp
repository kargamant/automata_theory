#include <Automat.h>
#include <string>
#include <iostream>
#include <format>
#include <set>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <queue>

namespace Automato
{
    const std::string Automat::alphabet="abcdefghijklmnopqrstuvwxyz0123456789";
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

    Automat::Automat(Automat& Automat1) : current(Automat1.current), id(Automat1.id), stateMap(Automat1.stateMap), start(Automat1.start), end(Automat1.end), accepting(Automat1.accepting)
    {
        //stateMap.merge(Automat1.stateMap);
    }

    Automat::Automat(Automat&& Automat1) :  stateMap(Automat1.stateMap), current(Automat1.current), id(Automat1.id), start(Automat1.start), end(Automat1.end), accepting(Automat1.accepting)
    {
        Automat1.current={""};
        Automat1.stateMap.clear();
    }

    Automat::Automat(int id, const std::string& transition) : id(id), current({"start_"+std::to_string(id)})
    {
        add_state("start_"+std::to_string(id));
        add_state("end_"+std::to_string(id));
        add_transition("start_"+std::to_string(id), "end_"+std::to_string(id), transition);
        start=getStart();
        end=getEnd();
        accepting.insert(end);
    }

    Automat& Automat::operator<<(Automat& automat)
    {
        if(this!=&automat && automat.id!=id)
        {
            stateMap.merge(automat.stateMap);
            start=automat.start;
            end=automat.end;
            //accepting.merge(automat.accepting);
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
            start=automat.start;
            end=automat.end;
            accepting=automat.accepting;
        }
        return *this;
    }

    Automat plusAutomat(Automat& Automat1)
    {
        Automat automat{Automat1};
        //considering every Automat have its start and end
        automat.add_transition(Automat1.getEnd(), Automat1.getStart(), "");
        //automat.accepting.insert(Automat1.getStart());
        return automat;
    }

    Automat optAutomat(Automat& Automat1)
    {
        Automat automat{Automat1};

        automat.add_transition(Automat1.getStart(), Automat1.getEnd(), "");
        //Automat1.accepting.insert(Automat1.start);
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
        automat.start=automat.getStart();
        automat.end=automat.getEnd();
        automat.accepting.clear();
        automat.accepting.insert(automat.end);
        automat.accepting.insert(Automat2.getEnd());
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
        automat.start=automat.getStart();
        automat.end=automat.getEnd();
        automat.accepting.clear();
        automat.accepting.insert(automat.end);
        automat.accepting.insert(Automat1.getEnd());
        automat.accepting.insert(Automat2.getEnd());
        return automat;
    }

    void Automat::printAutomat(std::ostream& stream)
    {
        stream<<"current_state_set:"<<std::endl;
        std::copy(current.begin(), current.end(), std::ostream_iterator<std::string>(stream, " "));
        stream<<std::endl;
        stream<<"accepting states:"<<std::endl;
        std::copy(accepting.begin(), accepting.end(), std::ostream_iterator<std::string>(stream, " "));
        stream<<std::endl;
        stream<<"start_state:"<<std::endl;
        stream<<start<<std::endl;
        stream<<"end_state:"<<std::endl;
        stream<<end<<std::endl;
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
            if(accepting.contains(state.first)) stream<<state.first<<"[color=\"green\"]"<<std::endl;
            if(state.first==start) stream<<state.first<<"[color=\"red\"]"<<std::endl;
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

    Automat nfaToDfa(Automat& automat)
    {
        Automat dfa;
        //std::cout<<"forming start candidates:"<<std::endl;
        StateSet start_candidates=formStateSet(automat, {automat.start}, "");
        start_candidates.set.insert(automat.start);
        std::queue<StateSet> queue;
        queue.push(start_candidates);
        std::vector<StateSet> added_sets;
        added_sets.push_back(start_candidates);
        dfa.start=start_candidates.getFullName();
        //start_candidates.print();
        dfa.add_state(start_candidates.getFullName());
        while(!queue.empty())
        {
            //bool isNew=true;
            auto candidate=queue.front();
            /*for(auto& added_set: added_sets)
            {
                if(added_set.set==candidate.set && candidate.set!=start_candidates.set)
                {
                    isNew=false;
                    break;
                }
            }
            if(!isNew)
            {
                queue.pop();
                continue;
            }*/

            for(auto& symb: Automat::alphabet)
            {
                auto symb_set=formStateSet(automat, candidate, {symb});
                auto eps_set=formStateSet(automat, symb_set, "");
                eps_set.set.merge(symb_set.set);
                if(!eps_set.set.empty())
                {
                    bool isNew=true;
                    StateSet same;
                    for(auto& added_set: added_sets)
                    {
                        if(added_set.set==eps_set.set)
                        {
                            isNew=false;
                            same=added_set;
                            break;
                        }
                    }
                    if(isNew)
                    {
                        queue.push(eps_set);
                        //std::cout<<std::format("Z_eps(T_{}({}))=", symb, candidate.getFullName());
                        //eps_set.print();
                        added_sets.push_back(eps_set);

                        dfa.add_state(eps_set.getFullName());
                        dfa.add_transition(candidate.getFullName(), eps_set.getFullName(), {symb});
                    }
                    else //if(eps_set.set==candidate.set)
                    {
                        dfa.add_transition(candidate.getFullName(), same.getFullName(), {symb});
                    }
                }
            }
            queue.pop();
        }

        for(auto& added_set: added_sets)
        {
            std::cout<<added_set.getFullName()<<std::endl;
            for(auto& state: added_set.set)
            {
                std::cout<<state<<std::endl<<std::endl;
                if(automat.accepting.contains(state))
                {
                    dfa.accepting.insert(added_set.getFullName());
                    break;
                }
            }
        }
        //std::cout<<"especcially for 1344:"<<std::endl;
        //std::cout<<automat.stateMap.contains("start_1344")<<std::endl;
        return dfa;
    }

    StateSet formStateSet(Automat& automat, const StateSet& stateSet, const std::string& transition)
    {
        std::set<std::string> set;
        for(auto& state: stateSet.set)
        {
            for(auto& st: automat.stateMap[state])
            {
                for(auto& tr: st.second)
                {
                    if(tr==transition)
                    {
                        set.insert(st.first);
                        break;
                    }
                }
            }
            auto result=formStateSet(automat, set, transition);
            std::move(result.set.begin(), result.set.end(), std::inserter<std::set<std::string>>(set, set.end()));
            //set.emplace(state);
        }
        return {set};
    }
}


