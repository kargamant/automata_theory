#include <Automat.h>
#include <Regex.h>
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
#include <random>

namespace Automato
{
    const std::string Automat::alphabet="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789{}?!+()-_*&^%,$#@!|'. ";
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
            if(!stateMap.contains(to)) add_state(to);
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
        if(accepting.contains(id)) accepting.erase(id);
    }
    /*void Automat::delete_transition(const std::string& from, const std::string& to, int i)
    {
        stateMap[from][to].erase(stateMap[from][to].begin()+i);
    }*/

    void Automat::delete_transition(int from, int to, const std::string& condition)
    {
        stateMap[from][to][condition]=false;

        bool emptyNow=true;
        for(auto& symb: stateMap[from][to])
        {
            if(symb.second)
            {
                emptyNow=false;
                break;
            }
        }
        if(emptyNow)
        {
            stateMap[from].erase(to);
        }
    }

    void Automat::add_capture_state(int id, const std::string& capture_name)
    {
        if(capture_groups.contains(capture_name)) capture_groups[capture_name].insert(id);
        else capture_groups.insert({capture_name, {id}});
    }

    void Automat::add_capture_all_states(const std::string& capture_name)
    {
        for(auto& st: stateMap) add_capture_state(st.first, capture_name);
    }

    void Automat::fill_search_capture_map()
    {
        if(!capture_groups.empty())
        {
            for(auto& cg: capture_groups)
            {
                for(auto& st: cg.second)
                {
                    if(!search_capture_map.contains(st)) search_capture_map.insert({st, {cg.first}});
                    else search_capture_map[st].insert(cg.first);
                }
            }
        }
    }

    Automat::Automat(Automat& Automat1) : current(Automat1.current), id(Automat1.id), stateMap(Automat1.stateMap), start(Automat1.start), end(Automat1.end), accepting(Automat1.accepting), capture_groups(Automat1.capture_groups)
    {
        //if(transitions_sieve.empty()) activate_transitions_sieve();
        //stateMap.merge(Automat1.stateMap);
    }

    Automat::Automat(Automat&& Automat1) :  stateMap(Automat1.stateMap), current(Automat1.current), id(Automat1.id), start(Automat1.start), end(Automat1.end), accepting(Automat1.accepting), capture_groups(Automat1.capture_groups)
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
            /*std::random_device rd;
            std::mt19937 rng(rd());
            std::uniform_int_distribution<std::mt19937::result_type> dist(1,100);

            for(auto& state: automat.stateMap)
            {
                int from=state.first;
                if(stateMap.contains(state.first)) from*=dist(rng);
                add_state(from);

                for(auto& to: state.second)
                {
                    int tow=to.first;
                    if(stateMap.contains(to.first)) tow*=dist(rng);
                    add_state(tow);
                    for(auto& symb: to.second)
                    {
                        if(symb.second) add_transition(from, tow, {symb.first});
                    }
                }
            }*/
            stateMap.merge(automat.stateMap);
            for(auto& cg: automat.capture_groups)
            {
                if(capture_groups.contains(cg.first)) capture_groups[cg.first].merge(cg.second);
                else capture_groups.insert({cg.first, cg.second});
            }
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
            capture_groups=automat.capture_groups;
            id=automat.id;
            start=automat.start;
            end=automat.end;
            accepting=automat.accepting;
        }
        return *this;
    }

    Automat productDfa(Automat& dfa1, Automat& dfa2)
    {
        Automat product;
        //dfa1.printAutomat();
        //dfa2.printAutomat();
        for(auto& p: dfa1.stateMap)
        {
            for(auto& q: dfa2.stateMap)
            {
                //std::cout<<"("<<p.first<<" "<<q.first<<")"<<std::endl;
                product.add_state(p.first*10+q.first);
            }
            //std::cout<<"("<<p.first<<" "<<"-q)"<<std::endl;
            //product.add_state(-p.first*10);
        }
        std::unordered_set<std::string> local_alphabet;
        for(auto& state: dfa1.getMap())
        {
            for(auto& to: state.second)
            {
                for(auto& symb: to.second)
                {
                    if(symb.second && !local_alphabet.contains(symb.first))
                    {
                        local_alphabet.insert(symb.first);
                    }
                }
            }
        }

        for(auto& state: dfa2.getMap())
        {
            for(auto& to: state.second)
            {
                for(auto& symb: to.second)
                {
                    if(symb.second && !local_alphabet.contains(symb.first))
                    {
                        local_alphabet.insert(symb.first);
                    }
                }
            }
        }
        /*for(auto& q: dfa2.stateMap)
        {
            std::cout<<"("<<q.first<<" "<<"-p)"<<std::endl;
            product.add_state(-q.first*10);
        }*/

        //product.printAutomat();

        for(auto& symb: local_alphabet)
        {
            for(auto& p: dfa1.stateMap)
            {
                for(auto& q: dfa2.stateMap)
                {
                    int p_to=0;
                    int q_to=0;
                    for(auto& p_tr: p.second)
                    {
                        if(p_tr.second[{symb}])
                        {
                            p_to=p_tr.first;
                            break;
                        }
                    }

                    for(auto& q_tr: q.second)
                    {
                        if(q_tr.second[{symb}])
                        {
                            q_to=q_tr.first;
                            break;
                        }
                    }

                    if(p_to==0 && q_to==0)
                    {
                        product.add_transition(p.first*10+q.first, 1, {symb});
                    }
                    else if(p_to!=0 && q_to!=0)
                    {
                        product.add_transition(p.first*10+q.first, p_to*10+q_to, {symb});
                    }
                    else if(p_to!=0)
                    {
                        product.add_transition(p.first*10+q.first, p_to*10-1, {symb});
                        //product.add_transition(p.first*10+q.first, -1, {symb});
                    }
                    else if(q_to!=0)
                    {
                        product.add_transition(p.first*10+q.first, q_to-10, {symb});
                        //product.add_transition(p.first*10+q.first, -1, {symb});

                    }
                }
            }
        }
        product.start=dfa1.start*10+dfa2.start;
        //product.printAutomat();
        //product.printDot();
        return product;
    }

    Automat differenceDfa(Automat& dfa1, Automat& dfa2)
    {
        dfa1.add_state(-1);
        dfa2.add_state(-1);
        Automat product=productDfa(dfa1, dfa2);
        //if(isCompliment) product.accepting.insert(-1);
        //product.printAutomat();
        for(auto& acc: dfa1.accepting)
        {
            for(auto& q: dfa2.stateMap)
            {
                if(!dfa2.accepting.contains(q.first)) product.accepting.insert(acc*10+q.first);
            }
        }
        //product.printAutomat();
        return product;
    }

    Automat complimentDfa(Automat& dfa)
    {
        std::unordered_set<std::string> local_alphabet;
        std::string alphabet_re;
        for(auto& state: dfa.getMap())
        {
            for(auto& to: state.second)
            {
                for(auto& symb: to.second)
                {
                    if(symb.second && !local_alphabet.contains(symb.first))
                    {
                        if(alphabet_re.empty()) alphabet_re+=symb.first;
                        else alphabet_re+="|"+symb.first;
                        local_alphabet.insert(symb.first);
                    }
                }
            }
        }
        alphabet_re=starEquivalent(alphabet_re);

        Automat alphabet_aut=Regex::Regex(alphabet_re).getAutomat();
        //alphabet_dfa.add_state(-1);
        //alphabet_dfa.accepting.insert(-1);
        /*Automat compliment{dfa};
        for(auto& state: compliment.stateMap)
        {
            if(compliment.accepting.contains(state.first))
            {
                compliment.accepting.erase(state.first);
            }
            else
            {
                compliment.accepting.insert(state.first);
            }
        }*/
        return differenceDfa(alphabet_aut, dfa);
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
        stream<<"capture groups:"<<std::endl;
        for(auto& cg: capture_groups)
        {
            stream<<"<"<<cg.first<<">"<<" | ";
            std::copy(cg.second.begin(), cg.second.end(), std::ostream_iterator<int>(stream, " "));
            stream<<std::endl;
        }
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
            //dfa.printAutomat();
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
                }
                if(!automat.capture_groups.empty())
                {
                    for(auto& cg: automat.capture_groups)
                    {
                        if(cg.second.contains(state))
                        {
                            //std::cout<<cg.first<<std::endl;
                            //std::cout<<state<<"->"<<added_set.second<<std::endl;
                            dfa.add_capture_state(added_set.second, cg.first);
                        }
                    }
                }
            }
        }
        return dfa;
    }

    StateSet formStateSet(Automat& automat, const StateSet& stateSet, const std::string& transition, bool isNfa)
    {
        std::unordered_set<int> set;
        //std::cout<<"transition: "<<transition<<std::endl;
        //std::cout<<"from set:"<<std::endl;
        //stateSet.print();
        //if(stateSet.set.empty()) return {set};
        for(auto& state: stateSet.set)
        {
            //std::cout<<"state: "<<state<<std::endl;
            for(auto& st: automat.stateMap[state])
            {
                //std::cout<<"to: "<<st.first<<std::endl;
                //std::cout<<"is transition: "<<st.second[transition]<<std::endl;
                if(st.second[transition] || (!isNfa && st.second["&"] && !std::string("?{}!+-.*&^%,$#@!|'").contains(transition)))
                {
                    set.insert(st.first);
                }
            }
            //std::cout<<"to for "<<state<<std::endl;
            //StateSet(set).print();
            if(isNfa)
            {
                auto result=formStateSet(automat, set, transition);
                //std::cout<<"result:"<<std::endl;
                //result.print();
                std::move(result.set.begin(), result.set.end(), std::inserter<std::unordered_set<int>>(set, set.end()));
            }
            //set.emplace(state);
        }
        return {set};
    }

    Automat minimizeDfa(Automat& dfa)
    {
        Automat minDfa;

        std::vector<StateSet> groups;
        if(dfa.capture_groups.empty())
        {

            groups.push_back(dfa.accepting);
            StateSet non_accepting;
            for(auto& state: dfa.stateMap)
            {
                if(!dfa.accepting.contains(state.first)) non_accepting.set.insert(state.first);
            }
            groups.push_back(non_accepting);
        }
        else
        {
            for(auto& cg: dfa.capture_groups)
            {
                groups.push_back(cg.second);
            }

            std::unordered_set<int> non_captured;
            for(auto& st: dfa.stateMap)
            {
                bool isNotCaptured=true;
                for(auto& cg: groups)
                {
                    if(cg.set.contains(st.first))
                    {
                        isNotCaptured=false;
                        break;
                    }
                }
                if(isNotCaptured) non_captured.insert(st.first);
            }
            groups.push_back(non_captured);
        }


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
                if(!dfa.capture_groups.empty())
                {
                    for(auto& cg: dfa.capture_groups)
                    {
                        if(cg.second.contains(state)) minDfa.add_capture_state(group.id, cg.first);
                    }
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


    std::unordered_map<std::string, std::string> Automat::verifyStr(const std::string& str, std::string& result, bool isNfa)
    {
        bool isValid=false;
        bool isFound=false;

        current.clear();
        current.insert(start);

        std::unordered_map<std::string, std::string> captures;
        if(!capture_groups.empty())
        {
            for(auto& cg: capture_groups) captures.insert({cg.first, ""});
        }

        std::unordered_set<std::string> current_cgs;
        std::vector<std::string> correctly_read;
        for(int i=0; i<str.size(); i++)
        {
            if(str[i]==' ' || str[i]=='\t')
            {
                if(isFound) break;
                current.clear();
                current.insert(start);
                result.clear();
                for(auto& cg: captures) cg.second.clear();
                for(auto& to: stateMap[start])
                {
                    if(to.second[{str[i]}])
                    {
                        i--;
                        break;
                    }
                }
            }
            //std::cout<<*current.begin()<<" "<<str[i]<<std::endl;
            for(auto& st: current)
            {
                /*std::cout<<st<<std::endl;
                for(auto& cg: search_capture_map[st]) std::cout<<cg<<std::endl;
                std::cout<<"current cgs:"<<std::endl;
                for(auto& cg: current_cgs) std::cout<<cg<<std::endl;
                std::cout<<std::endl;*/

                if(search_capture_map.contains(st) && current_cgs!=search_capture_map[st])
                {
                    if(current_cgs.size()>search_capture_map[st].size())
                    {
                        current_cgs=search_capture_map[st];
                        break;
                    }
                    else
                    {
                        std::unordered_set<std::string> new_current=search_capture_map[st];
                        for(auto& cg: current_cgs)
                        {
                            new_current.erase(cg);
                        }
                        current_cgs=new_current;
                        break;
                    }
                }
                else if(!search_capture_map.contains(st))
                {
                    current_cgs.clear();
                    break;
                }
            }
            for(auto& cg: current_cgs)
            {
                auto next=formStateSet(*this, current, {str[i]}, isNfa);
                bool differentState=false;
                for(auto& st: next.set)
                {
                    if(!search_capture_map.contains(st))
                    {
                        differentState=true;
                        break;
                    }
                    else if(search_capture_map[st]!=current_cgs)
                    {
                        std::unordered_set<std::string> intersection;
                        std::set_intersection(search_capture_map[st].begin(), search_capture_map[st].end(), current_cgs.begin(), current_cgs.end(), std::inserter(intersection, intersection.begin()));
                        //for(auto& inter: intersection) std::cout<<inter<<std::endl;
                        if(intersection.empty())
                        {
                            differentState=true;
                            break;
                        }
                    }
                }
                if(differentState) continue;
                captures[cg]+=str[i];
            }
            /*std::cout<<"current groups:"<<std::endl;
            for(auto& cg: current_cgs)
            {
                std::cout<<"<"<<cg<<">"<<std::endl;
            }
            std::cout<<"symbol: "<<str[i]<<std::endl;
            std::cout<<"captures:"<<std::endl;
            for(auto& cg: captures)
            {
                std::cout<<"<"<<cg.first<<">"<<": "<<cg.second<<std::endl;
            }
            std::cout<<std::endl;*/
            auto next_state=formStateSet(*this, current, {str[i]}, isNfa);

            if(next_state.set.empty())
            {
                if(isFound) break;
                current.clear();
                current.insert(start);
                result.clear();
                for(auto& cg: captures) cg.second.clear();
                for(auto& to: stateMap[start])
                {
                    if(to.second[{str[i]}])
                    {
                        i--;
                        break;
                    }
                }
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
                    correctly_read.push_back(result);
                    result.clear();
                    //return captures;
                }
            }
        }
        result.clear();
        for(auto& res: correctly_read) result+=res;
        return captures;
    }
    std::string Automat::recoverRe()
    {
        bool second_stage=false; //after all non accepting were eliminated
        for(int i=0; i<2; i++)
        {
	        std::vector<int> to_delete;
            std::vector<int> froms;
            std::vector<int> tos;
            std::vector<std::string> conditions;
	        for(auto& state: stateMap)
	        {
                if(second_stage && accepting.contains(state.first) && (stateMap[state.first].size()==0 || (stateMap[state.first].size()==1 && stateMap[state.first].contains(state.first)))) continue;
                if(start!=state.first)
                {
                    if(accepting.contains(state.first) && !second_stage)
                    {
                        continue;
                    }
                    //finding all enterances
	                std::unordered_map<int, std::unordered_set<std::string>> Q;
	                for(auto& q: stateMap)
	                {
	                    if(q.first!=state.first)
	                    {
	                        if(q.second.contains(state.first))
	                        {
	                            Q.insert({q.first, {}});
	                            for(auto& symb: q.second[state.first])
	                            {
	                                if(q.second[state.first][symb.first]) Q[q.first].insert(symb.first);
	                            }
	                        }
	                    }
	                }
	
	                //all exits
	                std::unordered_map<int, std::unordered_set<std::string>> P;
	                for(auto& st: stateMap[state.first])
	                {
	                    P.insert({st.first, {}});
	                    for(auto& symb: st.second)
	                    {
	                        if(symb.second) P[st.first].insert(symb.first);
	                    }
	                }

                    std::string postfix;
                    if(accepting.contains(state.first)) postfix="?";

	                //creating new transitions
	                for(auto& q: Q)
	                {
	                    for(auto& p: P)
	                    {
                            for(auto& q_tr: q.second)
	                        {
	                            for(auto& p_tr: p.second)
                                {
                                    /*if(p.first==state.first) continue;
                                    if(!stateMap[state.first].contains(state.first)) add_transition(q.first, p.first, q_tr+p_tr);
                                    else
                                    {
                                        std::string self_tr;
                                        for(auto& symb: stateMap[state.first][state.first])
                                        {
                                            if(symb.second)
                                            {
                                                self_tr=symb.first;
                                                break;
                                            }
                                        }
                                        add_transition(q.first, p.first, q_tr+starEquivalent(self_tr)+p_tr);
                                    }
                                    delete_transition(q.first, state.first, q_tr);
                                    delete_transition(state.first, p.first, p_tr);*/
                                    if(p.first==state.first) continue;
                                    std::string qr_tr, pr_tr, self_tr, direct_tr;

                                    if(stateMap[state.first].contains(q.first))
                                    {

                                        for(auto& qr: stateMap[state.first][q.first])
                                        {
                                            if(qr.second)
                                            {
                                                if(qr_tr.empty()) qr_tr+=qr.first;
                                                else qr_tr+="|"+qr.first;
                                            }
                                        }
                                    }

                                    if(stateMap[p.first].contains(state.first))
                                    {
                                        for(auto& pr: stateMap[p.first][state.first])
                                        {
                                            if(pr.second)
                                            {
                                                if(pr_tr.empty()) pr_tr+=pr.first;
                                                else pr_tr+="|"+pr.first;
                                            }
                                        }
                                    }

                                    if(stateMap[state.first].contains(state.first))
                                    {

                                        for(auto& symb: stateMap[state.first][state.first])
                                        {
                                            if(symb.second)
                                            {
                                                if(self_tr.empty()) self_tr+=symb.first;
                                                else self_tr+="|"+symb.first;
                                            }
                                        }
                                    }

                                    if(stateMap[q.first].contains(p.first))
                                    {
                                        for(auto& symb: stateMap[q.first][p.first])
                                        {
                                            if(symb.second)
                                            {
                                                if(direct_tr.empty()) direct_tr+=symb.first;
                                                else direct_tr+="|"+symb.first;
                                            }
                                        }
                                    }

                                    if(q.first==p.first)
                                    {
                                        add_transition(q.first, p.first, q_tr+starEquivalent(self_tr)+postfixString(p_tr, postfix));
                                        froms.push_back(q.first);
                                        tos.push_back(state.first);
                                        conditions.push_back(q_tr);
                                        //delete_transition(q.first, state.first, q_tr);
                                        froms.push_back(state.first);
                                        tos.push_back(p.first);
                                        conditions.push_back(p_tr);
                                        //delete_transition(state.first, p.first, p_tr);
                                        if(!self_tr.empty())
                                        {
                                            froms.push_back(state.first);
                                            tos.push_back(state.first);
                                            conditions.push_back(self_tr);
                                            //delete_transition(state.first, state.first, self_tr);
                                        }
                                        continue;
                                    }
                                    //std::cout<<q.first<<"->"<<p.first<<" "<<q_tr+starEquivalent(starEquivalent(self_tr)+qr_tr+q_tr)+starEquivalent(self_tr)+p_tr+starEquivalent(pr_tr+starEquivalent(self_tr)+p_tr)<<std::endl;
                                    if(!qr_tr.empty() && !pr_tr.empty())
                                    {
                                        //std::cout<<q.first<<"->"<<p.first<<" "<<q_tr+starEquivalent(starEquivalent(self_tr)+qr_tr+q_tr)+starEquivalent(self_tr)+postfixString(p_tr, postfix)+starEquivalent(pr_tr+starEquivalent(self_tr)+postfixString(p_tr, postfix))<<std::endl;
                                        add_transition(q.first, p.first, q_tr+starEquivalent(starEquivalent(self_tr)+qr_tr+q_tr)+starEquivalent(self_tr)+postfixString(p_tr, postfix)+starEquivalent(pr_tr+starEquivalent(self_tr)+postfixString(p_tr, postfix)));
                                        froms.push_back(state.first);
                                        tos.push_back(q.first);
                                        conditions.push_back(qr_tr);
                                        //delete_transition(state.first, q.first, qr_tr);
                                        froms.push_back(p.first);
                                        tos.push_back(state.first);
                                        conditions.push_back(pr_tr);
                                        //delete_transition(p.first, state.first, pr_tr);
                                    }
                                    else if(!qr_tr.empty())
                                    {
                                        //std::cout<<q.first<<"->"<<p.first<<" "<<q_tr+starEquivalent(starEquivalent(self_tr)+qr_tr+q_tr)+starEquivalent(self_tr)+postfixString(p_tr, postfix)<<std::endl;
                                        add_transition(q.first, p.first, q_tr+starEquivalent(starEquivalent(self_tr)+qr_tr+q_tr)+starEquivalent(self_tr)+postfixString(p_tr, postfix));
                                        froms.push_back(state.first);
                                        tos.push_back(q.first);
                                        conditions.push_back(qr_tr);
                                        //delete_transition(state.first, q.first, qr_tr);
                                    }
                                    else if(!pr_tr.empty())
                                    {
                                        //std::cout<<q.first<<"->"<<p.first<<" "<<q_tr+starEquivalent(self_tr)+postfixString(p_tr, postfix)+starEquivalent(pr_tr+starEquivalent(self_tr)+postfixString(p_tr, postfix))<<std::endl;
                                        add_transition(q.first, p.first, q_tr+starEquivalent(self_tr)+p_tr+postfix+starEquivalent(pr_tr+starEquivalent(self_tr)+postfixString(p_tr, postfix)));
                                        froms.push_back(p.first);
                                        tos.push_back(state.first);
                                        conditions.push_back(pr_tr);
                                        //delete_transition(p.first, state.first, pr_tr);
                                    }
                                    else
                                    {
                                        //std::cout<<q.first<<"->"<<p.first<<" "<<q_tr+starEquivalent(self_tr)+postfixString(p_tr, postfix)<<std::endl;
                                        add_transition(q.first, p.first, q_tr+starEquivalent(self_tr)+postfixString(p_tr, postfix));
                                    }
                                    froms.push_back(q.first);
                                    tos.push_back(state.first);
                                    conditions.push_back(q_tr);
                                    //delete_transition(q.first, state.first, q_tr);
                                    froms.push_back(state.first);
                                    tos.push_back(p.first);
                                    conditions.push_back(p_tr);
                                    //delete_transition(state.first, p.first, p_tr);
                                    if(!self_tr.empty())
                                    {
                                        froms.push_back(state.first);
                                        tos.push_back(state.first);
                                        conditions.push_back(self_tr);
                                        //delete_transition(state.first, state.first, self_tr);
                                    }

                                    /*
                                    if(!stateMap[state.first].contains(state.first) && !stateMap[p.first].contains(state.first))
                                    {
                                        add_transition(q.first, p.first, q_tr+p_tr+postfix);
                                    }
                                    else if(!stateMap[state.first].contains(state.first) && stateMap[p.first].contains(state.first))
                                    {
                                        std::string loop="("+p_tr;
                                        for(auto& tr: stateMap[p.first][state.first])
                                    }
	                                else
	                                {
	                                    std::string self_tr;
	                                    for(auto& symb: stateMap[state.first][state.first])
	                                    {
	                                        if(symb.second)
	                                        {
	                                            self_tr=symb.first;
	                                            break;
	                                        }
	                                    }
                                        add_transition(q.first, p.first, q_tr+starEquivalent(self_tr)+p_tr+postfix);
                                    }*/
                                    //printAutomat();
                                    //printDot();
                                }
	                        }
	                    }
                        for(int i=0; i<froms.size(); i++)
                        {
                            if(froms[i]!=tos[i]) delete_transition(froms[i], tos[i], conditions[i]);
                        }
                        //froms.clear();
                        //tos.clear();
                        //conditions.clear();
                        to_delete.push_back(state.first);
                    }
	                //delete_state(state.first);
	            }
            }
                        for(int i=0; i<froms.size(); i++)
                        {
                            delete_transition(froms[i], tos[i], conditions[i]);
                        }
                        froms.clear();
                        tos.clear();
                        conditions.clear();
            for(auto& st: to_delete) delete_state(st);
            to_delete.clear();
            second_stage=true;
            //printAutomat();
            //printDot();
        }
        printAutomat();
        printDot();

        int Start=start;
        std::string re;
        for(auto& acc: accepting)
        {
            std::string R;
            int End=acc;
            std::string V, S; // V - self_transition for start, S - transition to end state
            std::string U, T; // U - self_transition for end, T - back transition to start state

            V=fillTransitions(Start, Start);
            S=fillTransitions(Start, End);
            U=fillTransitions(End, End);
            T=fillTransitions(End, Start);

            std::cout<<V<<" "<<S<<" "<<U<<" "<<T<<std::endl;

            if(V.empty() && !T.empty()) R=starEquivalent("("+S+starEquivalent(U)+T+")")+S+starEquivalent(U);
            else if(!V.empty() && T.empty()) R=starEquivalent(V)+S+starEquivalent(U);
            else if(V.empty() && T.empty()) R=S+starEquivalent(U);
            else
            {
                R=starEquivalent("("+V+"|"+S+starEquivalent(U)+T+")")+S+starEquivalent(U);
            }
            if(re.empty()) re+="("+R+")";
            else re+="|("+R+")";
        }

        return re;
    }
    std::string Automat::fillTransitions(int from, int to)
    {
        std::string result;
        for(auto& tr: stateMap[from][to])
        {
            if(tr.second)
            {
                if(!result.empty()) result+="|"+tr.first;
                else result+=tr.first;
            }
        }
        return result;
    }
    std::string starEquivalent(const std::string& node)
    {
        if(node.empty()) return "";
        return "(("+node+"){0,1}|"+"("+node+")+)";
    }

    std::string postfixString(const std::string& str, const std::string& postfix)
    {
        if(str.empty()) return "";
        else if(str.size()==1) return str+postfix;
        else return "("+str+")"+postfix;
    }
    std::string orString(const std::string& str1, const std::string& str2)
    {
        if(str1.empty() &&str2.empty()) return "";
        else if(str1.empty()) return str2;
        else if(str2.empty()) return str1;
        else
        {
            return "("+str1+")"+"|"+"("+str2+")";
        }
    }
}


