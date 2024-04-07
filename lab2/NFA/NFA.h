#ifndef AUTOMAT_H
#define AUTOMAT_H
#include <unordered_map>
#include <string>

namespace Nfa
{
    class NFA
    {
    private:
        //structure of table
        //from | <to, how>
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> stateMap;
        std::string current;
        int id;

        void add_state(const std::string& name);
        void add_transition(const std::string& from, const std::string& to, const std::string& condition);
        void delete_state(const std::string& name);
        void delete_transition(const std::string& from, const std::string& to);
    public:
        NFA();
        NFA(int id, const std::string& transition);
        NFA(NFA& NFA1);
        NFA(NFA&& NFA1);
        NFA(NFA& NFA1, NFA& NFA2, char op);
        NFA(NFA& NFA1, char op);

        std::string getStart() {return "start_"+std::to_string(id);}
        std::string getEnd() {return "end_"+std::to_string(id);}

        NFA& operator<<(NFA& nfa);

        friend NFA orNFA(NFA& NFA1, NFA& NFA2);
        friend NFA catNFA(NFA& NFA1, NFA& NFA2);
        friend NFA plusNFA(NFA& NFA1);
        friend NFA optNFA(NFA& NFA1);
        friend NFA anyNFA(int id);
    };
    NFA orNFA(NFA& NFA1, NFA& NFA2);
    NFA catNFA(NFA& NFA1, NFA& NFA2);
    NFA plusNFA(NFA& NFA1);
    NFA optNFA(NFA& NFA1);
    NFA anyNFA(int id);
}

#endif // AUTOMAT_H
