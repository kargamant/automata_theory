#include <Automat.h>
#include <string>
#include <iostream>
#include <format>
#include <set>
#include <vector>
#include <iterator>
#include <unordered_map>
#include <queue>
#include <algorithm>

namespace Automato
{
    const std::string Automat::alphabet="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789{}?!+-*&^%$#@!|. ";
    void Automat::add_state(const std::string& name)
    {
        stateMap.insert({name, std::unordered_map<std::string, std::vector<std::string>>()});
    }

    void Automat::add_transition(const std::string& from, const std::string& to, const std::string& condition)
    {
        if(stateMap[from].contains(to) && std::find(stateMap[from][to].begin(), stateMap[from][to].end(), condition)==stateMap[from][to].end()) stateMap[from][to].push_back(condition);
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
                    if(condition!="") stream<<state.first<<"->"<<transition.first<<" [label=\""<<condition<<"\"]"<<std::endl;
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
                /*if(eps_set.getFullName()=="StateSet48791" || eps_set.getFullName()=="StateSet48494")
                {
                    std::cout<<"debug"<<std::endl;
                    eps_set.print();
                }*/
                //std::cout<<eps_set.getFullName()<<std::endl;
                //std::cout<<eps_set.set.empty()<<std::endl;
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
            //std::cout<<added_set.getFullName()<<std::endl;
            for(auto& state: added_set.set)
            {
                //std::cout<<state<<std::endl<<std::endl;
                if(automat.accepting.contains(state))
                {
                    dfa.accepting.insert(added_set.getFullName());
                    break;
                }
            }
        }
        return dfa;
    }

    StateSet formStateSet(Automat& automat, const StateSet& stateSet, const std::string& transition, bool isNfa)
    {
        std::set<std::string> set;
        for(auto& state: stateSet.set)
        {
            for(auto& st: automat.stateMap[state])
            {
                for(auto& tr: st.second)
                {
                    if(tr==transition || (!isNfa && tr=="&"))
                    {
                        set.insert(st.first);
                        break;
                    }

                }
            }
            if(isNfa)
            {
                auto result=formStateSet(automat, set, transition);
                std::move(result.set.begin(), result.set.end(), std::inserter<std::set<std::string>>(set, set.end()));
            }
            //set.emplace(state);
        }
        return {set};
    }

    Automat minimizeDfa(Automat& dfa)
    {
        Automat minDfa;

        std::set<StateSet> groups{dfa.accepting};
        StateSet non_accepting;
        for(auto& state: dfa.stateMap)
        {
            if(!dfa.accepting.contains(state.first)) non_accepting.set.insert(state.first);
        }
        groups.insert(non_accepting);

        bool noChanges=false;
        std::set<StateSet> new_groups;
        std::set<std::string> to_leave;
        while(!noChanges)
        {
            int set_size=new_groups.size();
            //std::cout<<"debug"<<std::endl;
            /*for(auto& group: groups)
            {
                std::cout<<"Group:"<<std::endl;
                group.print();
            }*/
            noChanges=true;
            std::vector<StateSet> to_eliminate;
            std::set<std::string> checked_groups;
            for(auto& group: groups)
            {
                StateSet group_copy=group;
                if(group.set.size()==1) continue;

                bool groupsCreated=false;
                for(auto& state1: group.set)
                {

                    for(auto& state2: group.set)
                    {
                        if(checked_groups.contains(state2)) continue;
                        if(state1==state2) continue;

                        //std::cout<<"states pair:"<<std::endl;
                        //std::cout<<"( "<<state1<<", "<<state2<<" )"<<std::endl;
                        for(auto& symb: Automat::alphabet)
                        {
                            std::string dest1;
                            std::string dest2;
                            for(auto& to: dfa.stateMap[state1])
                            {
                                bool isFound=false;
                                for(auto& transition: to.second)
                                {
                                    if(transition==std::string{symb})
                                    {
                                        dest1=to.first;
                                        isFound=true;
                                        break;
                                    }
                                }
                                if(isFound) break;
                            }

                            for(auto& to: dfa.stateMap[state2])
                            {
                                bool isFound=false;
                                for(auto& transition: to.second)
                                {
                                    if(transition==std::string{symb})
                                    {
                                        dest2=to.first;
                                        isFound=true;
                                        break;
                                    }
                                }
                                if(isFound) break;
                            }
                            //std::cout<<"symb: "<<symb<<std::endl;
                            //std::cout<<"destinations: "<<dest1<<" "<<dest2<<std::endl;
                            if(dest1.empty() && dest2.empty()) continue;
                            else if((dest1.empty() && !dest2.empty()) || (!dest1.empty() && dest2.empty()))
                            {
                                groupsCreated=true;
                                StateSet ss1{state1};
                                //StateSet ss2{state2};

                                /*for(auto& state: group.set)
                                {
                                    if(state!=state1 && state!=state2)
                                    {
                                        ss1.set.insert(state);
                                        ss2.set.insert(state);
                                    }
                                }*/
                                new_groups.insert(ss1);
                                //new_groups.insert(ss2);
                                to_eliminate.push_back(group);

                                group_copy.set.erase(state1);
                                //group_copy.set.erase(state2);

                                if(!group_copy.set.empty()) new_groups.insert(group_copy);
                                to_eliminate.push_back(group);

                                //std::cout<<"changes:"<<std::endl;
                                //for(auto& gr: new_groups) gr.print();
                                break;
                            }
                            //else if((dest1.empty() && !dest2.empty()) || (!dest1.empty() && dest2.empty())) continue;
                            for(auto& gr: groups)
                            {
                                if((gr.set.contains(dest1) && !gr.set.contains(dest2)) || (!gr.set.contains(dest1) && gr.set.contains(dest2)))
                                {
                                    groupsCreated=true;
                                    //StateSet ss1{state1};
                                    StateSet ss2{state2};


                                    /*for(auto& state: group.set)
                                    {
                                        if(state!=state1 && state!=state2)
                                        {
                                            ss1.set.insert(state);
                                            ss2.set.insert(state);
                                        }
                                    }*/
                                    //new_groups.insert(ss1);
                                    new_groups.insert(ss2);
                                    to_eliminate.push_back(group);
                                    //group_copy.set.erase(state1);
                                    group_copy.set.erase(state2);

                                    if(!group_copy.set.empty()) new_groups.insert(group_copy);
                                    to_eliminate.push_back(group);

                                    //std::cout<<"changes:"<<std::endl;
                                    //for(auto& gr: new_groups) gr.print();
                                    break;
                                }
                            }

                            //danger zone
                            //groups.erase(group);
                            //groups.insert(gr);
                            if(groupsCreated) break;
                        }
                        if(groupsCreated) break;
                    }
                    checked_groups.insert(state1);
                    if(groupsCreated) break;
                }
                if(groupsCreated) break;
            }

            if(set_size!=new_groups.size() && !new_groups.empty())
            {
                //std::cout<<"new ones:"<<std::endl;
                //std::cout<<new_groups.size()<<std::endl;
                //std::cout<<new_groups.empty()<<std::endl;
                /*for(auto& new_group: new_groups)
                {
                    std::cout<<"new Group:"<<std::endl;
                    new_group.print();
                }*/
                noChanges=false;
                groups.merge(new_groups);
                for(auto& target_group: to_eliminate)
                {
                    //std::cout<<"eliminating:"<<std::endl;
                    //target_group.print();
                    groups.erase(target_group);
                }
            }
            //new_groups.clear();
        }

        /*std::cout<<"end:"<<std::endl;
        for(auto& group: groups)
        {
            std::cout<<"Group:"<<std::endl;
            group.print();
        }*/

        for(auto& group: groups)
        {
            minDfa.add_state(group.getFullName());
            for(auto& state: group.set)
            {
                if(dfa.accepting.contains(state))
                {
                    minDfa.accepting.insert(group.getFullName());
                }
                if(state==dfa.start)
                {
                    minDfa.start=group.getFullName();
                }
            }
        }

        for(auto& group1: groups)
        {
            for(auto& state: group1.set)
            {
                for(auto& to: dfa.stateMap[state])
                {
                    for(auto& transition: to.second)
                    {
                        for(auto& group2: groups)
                        {
                            //if(group1.set==group2.set) continue;
                            if(group2.set.contains(to.first))
                            {
                                auto transitions=minDfa.stateMap[group2.getFullName()][to.first];
                                minDfa.add_transition(group1.getFullName(), group2.getFullName(), transition);
                            }
                        }
                    }
                }
            }
        }
        //std::cout<<"Automat:"<<std::endl;
        //minDfa.printDot();
        return minDfa;
    }


    bool Automat::verifyStr(const std::string& str, std::string& result, bool isNfa)
    {
        bool isValid=false;
        bool isFound=false;

        current.clear();
        current.insert(start);

        for(int i=0; i<str.size(); i++)
        {
            isValid=false;
            auto next_state=formStateSet(*this, current, {str[i]}, isNfa);

            if(next_state.set.empty())
            {
                if(isFound) break;
                current.clear();
                current.insert(start);
                result.clear();
                continue;
            }

            if(isNfa)
            {
                auto eps_set=formStateSet(*this, next_state.set, "");
                if(!eps_set.set.empty()) next_state.set.merge(eps_set.set);
            }

            current=next_state.set;
            result+=str[i];
            for(auto& acc: accepting)
            {
                if(current.contains(acc))
                {
                    isValid=true;
                    isFound=true;
                    break;
                }
            }
        }

        return isValid;
    }
}


