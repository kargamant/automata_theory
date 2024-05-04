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
#include <cmath>

namespace Automato
{
    const std::string Automat::alphabet="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789{}?!+-*&^%,$#@!|. ";
    std::unordered_map<std::string, bool> Automat::transitions_sieve{{"a", false}};


    void Automat::activate_transitions_sieve()
    {
        for(auto& symb: alphabet)
        {
            transitions_sieve.insert({{symb}, false});
        }
    }

    void Automat::add_state(int id)
    {
        stateMap.insert({id, std::unordered_map<int, std::unordered_map<std::string, bool>>()});
    }

    void Automat::add_transition(int from, int to, const std::string& condition)
    {
        if(stateMap[from].contains(to) && !stateMap[from][to][condition]) stateMap[from][to][condition]=true;
        else
        {
            stateMap[from].insert({to, transitions_sieve});
            stateMap[from][to][condition]=true;
        }
    }


    void Automat::delete_state(int id)
    {
        stateMap.erase(id);
        for(auto& state: stateMap)
        {
            state.second.erase(id);
        }
    }
    /*void Automat::delete_transition(const std::string& from, const std::string& to, int i)
    {
        stateMap[from][to].erase(stateMap[from][to].begin()+i);
    }*/

    void Automat::delete_transition(int from, int to, const std::string& condition)
    {
        stateMap[from][to][condition]=false;
    }

    Automat::Automat(Automat& Automat1) : current(Automat1.current), id(Automat1.id), stateMap(Automat1.stateMap), start(Automat1.start), end(Automat1.end), accepting(Automat1.accepting)
    {
        //if(transitions_sieve.empty()) activate_transitions_sieve();
        //stateMap.merge(Automat1.stateMap);
    }

    Automat::Automat(Automat&& Automat1) :  stateMap(Automat1.stateMap), current(Automat1.current), id(Automat1.id), start(Automat1.start), end(Automat1.end), accepting(Automat1.accepting)
    {
        //if(transitions_sieve.empty()) activate_transitions_sieve();
        Automat1.current={};
        Automat1.stateMap.clear();
    }

    Automat::Automat(int id, const std::string& transition) : id(id), current({id})
    {
        if(transitions_sieve.empty()) activate_transitions_sieve();

        add_state(id);
        add_state(-id);
        add_transition(id, -id, transition);
        start=id;
        end=-id;
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


    Automat rangeAutomat(Automat& automat, int min, int max)
    {
        //to be fixed
        Automat rangeAutomat{automat};
        //rangeAutomat.printAutomat();
        Automat resultAutomat{automat};
        for(int i=0; i<max-1; i++)
        {
            //std::cout<<"range_debug"<<std::endl;
            //resultAutomat.printAutomat();
            Automat rangeCopy;
            for(auto& state: rangeAutomat.stateMap)
            {
                rangeCopy.add_state(state.first+(state.first>0 ? ((i+1)*automat.start) : (-(i+1)*automat.start)));
            }
            for(auto& state: rangeAutomat.stateMap)
            {
                for(auto& to: state.second)
                {
                    for(auto& tr: to.second)
                    {
                        //may be incorrect after optimization
                        if(tr.second) rangeCopy.add_transition(state.first+(state.first>0 ? ((i+1)*automat.start) : (-(i+1)*automat.start)), to.first+(to.first>0 ? ((i+1)*automat.start) : (-(i+1)*automat.start)), tr.first);
                    }
                }
            }
            rangeCopy.start=rangeAutomat.start+(i+1)*automat.start;
            rangeCopy.end=rangeAutomat.end-(i+1)*automat.start;
            rangeCopy.accepting.clear();
            rangeCopy.current.clear();
            for(auto& acc: rangeAutomat.accepting) rangeCopy.accepting.insert(acc+(acc>0 ? (i+1)*automat.start : -(i+1)*automat.start));
            for(auto& cur: rangeAutomat.current) rangeCopy.current.insert(cur+(cur>0 ? (i+1)*automat.start : -(i+1)*automat.start));

            //std::cout<<"range copy:"<<std::endl;
            //rangeCopy.printAutomat();

            int end=resultAutomat.end;
            resultAutomat<<rangeCopy;
            resultAutomat.add_transition(end, rangeCopy.start, "");
            resultAutomat.end=rangeCopy.end;
            resultAutomat.current=rangeCopy.current;
            resultAutomat.accepting=rangeCopy.accepting;
            resultAutomat.start=rangeAutomat.start;
        }
        for(int i=min; i<max; i++)
        {
            if(i==0) resultAutomat.add_transition(rangeAutomat.start, rangeAutomat.end-(max-1)*automat.start, "");
            else if(i==1) resultAutomat.add_transition(rangeAutomat.end, rangeAutomat.end-(max-1)*automat.start, "");
            else resultAutomat.add_transition(rangeAutomat.end-(i-1)*automat.start, rangeAutomat.end-(max-1)*automat.start, "");
        }

        //resultAutomat.printAutomat();
        //resultAutomat.printDot();
        return resultAutomat;
    }

    Automat plusAutomat(Automat& Automat1)
    {
        Automat automat{Automat1};
        //considering every Automat have its start and end
        automat.add_transition(Automat1.end, Automat1.start, "");
        //automat.accepting.insert(Automat1.getStart());
        return automat;
    }

    Automat optAutomat(Automat& Automat1)
    {
        Automat automat{Automat1};

        automat.add_transition(Automat1.start, Automat1.end, "");
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
        automat.add_state(automat.id);
        automat.add_state(-automat.id);
        automat.start=automat.id;
        automat.end=-automat.id;

        automat.add_transition(automat.start, Automat1.start, "");
        automat.add_transition(Automat2.end, automat.end, "");

        automat.add_transition(Automat1.end, Automat2.start, "");
        automat.accepting.clear();
        automat.accepting.insert(automat.end);
        automat.accepting.insert(Automat2.end);
        return automat;
    }

    Automat orAutomat(Automat& Automat1, Automat& Automat2)
    {
        Automat automat{Automat1};
        auto stateMap_copy=Automat2.stateMap;
        automat<<Automat2;
        Automat2.stateMap=stateMap_copy;
        automat.id=Automat1.id+Automat2.id;
        automat.add_state(automat.id);
        automat.add_state(-automat.id);
        automat.start=automat.id;
        automat.end=-automat.id;

        automat.add_transition(automat.start, Automat1.start, "");
        automat.add_transition(automat.start, Automat2.start, "");

        automat.add_transition(Automat1.end, automat.end, "");
        automat.add_transition(Automat2.end, automat.end, "");
        automat.accepting.clear();
        automat.accepting.insert(automat.end);
        automat.accepting.insert(Automat1.end);
        automat.accepting.insert(Automat2.end);
        return automat;
    }

    void Automat::printAutomat(std::ostream& stream)
    {
        stream<<"current_state_set:"<<std::endl;
        std::copy(current.begin(), current.end(), std::ostream_iterator<int>(stream, " "));
        stream<<std::endl;
        stream<<"accepting states:"<<std::endl;
        std::copy(accepting.begin(), accepting.end(), std::ostream_iterator<int>(stream, " "));
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
                    if(condition.second) stream<<std::format("(\"{}\", \"{}\")", std::to_string(transition.first), condition.first)<<" ;";
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
            if(accepting.contains(state.first)) stream<<"\""<<state.first<<"\""<<"[color=\"green\"]"<<std::endl;
            if(state.first==start) stream<<"\""<<state.first<<"\""<<"[color=\"red\"]"<<std::endl;
            for(auto& transition: state.second)
            {
                for(auto& condition: transition.second)
                {
                    if(condition.first!="" && condition.second) stream<<"\""<<state.first<<"\""<<"->"<<"\""<<transition.first<<"\""<<" [label=\""<<condition.first<<"\"]"<<std::endl;
                    else if(condition.second) stream<<"\""<<state.first<<"\""<<"->"<<"\""<<transition.first<<"\""<<" [label=ε]"<<std::endl;
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
        std::unordered_map<std::unordered_set<int>, int, unorderedSetHash> added_sets;
        added_sets.insert({start_candidates.set, start_candidates.id});
        dfa.start=start_candidates.id;
        //start_candidates.print();
        dfa.add_state(start_candidates.id);
        while(!queue.empty())
        {
            //bool isNew=true;
            auto candidate=queue.front();
            //candidate.print();
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
                //symb_set.print();
                auto eps_set=formStateSet(automat, symb_set, "");
                //eps_set.print();
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
                    if(added_sets.contains(eps_set.set)) dfa.add_transition(candidate.id, added_sets[eps_set.set], {symb});
                    else
                    {
                        queue.push(eps_set);
                        //std::cout<<std::format("Z_eps(T_{}({}))=", symb, candidate.getFullName());
                        //eps_set.print();
                        added_sets.insert({eps_set.set, eps_set.id});

                        dfa.add_state(eps_set.id);
                        dfa.add_transition(candidate.id, eps_set.id, {symb});
                    }
                    /*
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

                        dfa.add_state(eps_set.id);
                        dfa.add_transition(candidate.id, eps_set.id, {symb});
                    }
                    else //if(eps_set.set==candidate.set)
                    {
                        dfa.add_transition(candidate.id, same.id, {symb});
                    }*/
                }
            }
            queue.pop();
        }

        for(auto& added_set: added_sets)
        {
            //std::cout<<added_set.getFullName()<<std::endl;
            for(auto& state: added_set.first)
            {
                //std::cout<<state<<std::endl<<std::endl;
                if(automat.accepting.contains(state))
                {
                    dfa.accepting.insert(added_set.second);
                    break;
                }
            }
        }
        return dfa;
    }

    StateSet formStateSet(Automat& automat, const StateSet& stateSet, const std::string& transition, bool isNfa)
    {
        std::unordered_set<int> set;
        for(auto& state: stateSet.set)
        {
            for(auto& st: automat.stateMap[state])
            {
                if(st.second[transition] || (!isNfa && st.second["&"]))
                {
                    set.insert(st.first);
                }
            }
            if(isNfa)
            {
                auto result=formStateSet(automat, set, transition);
                std::move(result.set.begin(), result.set.end(), std::inserter<std::unordered_set<int>>(set, set.end()));
            }
            //set.emplace(state);
        }
        return {set};
    }

    Automat minimizeDfa(Automat& dfa)
    {
        Automat minDfa;

        std::vector<StateSet> groups{dfa.accepting};
        StateSet non_accepting;
        for(auto& state: dfa.stateMap)
        {
            if(!dfa.accepting.contains(state.first)) non_accepting.set.insert(state.first);
        }
        groups.push_back(non_accepting);


        bool noChanges=false;
        while(!noChanges)
        {
            noChanges=true;
            for(int i=0; i<groups.size(); i++)
            {
                //obviously nothing to distinguish
                if(groups[i].set.size()==1) continue;

                //this is kind of sieve/matrix which represents relationship between different states in group
                //This is different statuses of two states:
                //0 on the intersection of Si and Sj means that Si and Sj must remain in that group together
                //1 on the intersection of Si and Sj means that Si and Sj must be distinguished
                //-1 can appear only on intersection of Si and Si itself just to identify that it's not different states
                //-2 can appear only on intersection of Si and Si itself to mark it as distinguished. As soon as Si has -2 it's no more in this group
                std::unordered_map<int, std::unordered_map<int, int>> distinguishMap;

                //filling sieve
                for(auto& st1: groups[i].set)
                {
                    distinguishMap.insert({st1, std::unordered_map<int, int>()});
                    for(auto& st2: groups[i].set)
                    {
                        if(st1!=st2)
                        {
                            distinguishMap[st1].insert({st2, 0});
                        }
                        else
                        {
                            distinguishMap[st1].insert({st2, -1});
                        }
                    }
                }

                for(auto& state1: groups[i].set)
                {
                    for(auto& state2: groups[i].set)
                    {
                        if(distinguishMap[state1][state2]!=0) continue;

                        for(auto& symb: Automat::alphabet)
                        {
                            int dest1=-1;
                            int dest2=-1;
                            for(auto& to: dfa.stateMap[state1])
                            {
                                if(to.second[{symb}])
                                {
                                    dest1=to.first;
                                    break;
                                }
                            }

                            for(auto& to: dfa.stateMap[state2])
                            {
                                if(to.second[{symb}])
                                {
                                    dest2=to.first;
                                    break;
                                }
                            }

                            //both has no transition by this symbol
                            if(dest1==-1 && dest2==-1) continue;

                            //must be distinguished if one of them doesn't have transition and other does
                            else if((dest1==-1 && dest2!=-1) || (dest1!=-1 && dest2==-1))
                            {
                                distinguishMap[state1][state2]=1;
                                distinguishMap[state2][state1]=1;
                            }
                            else
                            {
                                for(auto& gr: groups)
                                {
                                    //distinguish if they are in f=different groups
                                    if((gr.set.contains(dest1) && !gr.set.contains(dest2)) || (!gr.set.contains(dest1) && gr.set.contains(dest2)))
                                    {
                                        distinguishMap[state1][state2]=1;
                                        distinguishMap[state2][state1]=1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
                for(auto& ds: distinguishMap)
                {
                    if(ds.second[ds.first]==-2) continue;

                    //collecting set to distinguish
                    StateSet toDistinguish{ds.first};
                    for(auto& connections: ds.second)
                    {
                        if(connections.second==0)
                        {
                            toDistinguish.set.insert(connections.first);
                        }
                    }

                    //the base case is when the group cant be separated no more, so we should leave it
                    if(toDistinguish.set==groups[i].set) break;
                    else
                    {
                        noChanges=false;
                        groups.push_back(toDistinguish);
                        for(auto& target: toDistinguish.set)
                        {
                            distinguishMap[target][target]=-2;
                            groups[i].set.erase(target);
                        }
                    }
                }
            }
        }
        //std::cout<<"group distribution:"<<std::endl;
        /*for(auto& gr: groups)
        {
            gr.print();
        }*/

        for(auto& group: groups)
        {
            minDfa.add_state(group.id);
            for(auto& state: group.set)
            {
                if(dfa.accepting.contains(state))
                {
                    minDfa.accepting.insert(group.id);
                }
                if(state==dfa.start)
                {
                    minDfa.start=group.id;
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
                            if(group2.set.contains(to.first) && to.second[transition.first])
                            {
                                //auto transitions=minDfa.stateMap[group2.getFullName()][to.first];
                                minDfa.add_transition(group1.id, group2.id, transition.first);
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
            auto next_state=formStateSet(*this, current, {str[i]}, isNfa);

            if(next_state.set.empty())
            {
                if(isFound) break;
                current.clear();
                current.insert(start);
                result.clear();
                continue;
            }

            isValid=false;
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
                    return isValid;
                }
            }
        }
        return isValid;
    }
}


