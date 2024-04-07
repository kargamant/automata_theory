#ifndef AUTOMAT_H
#define AUTOMAT_H
#include <unordered_map>

namespace Nfa
{
    class NFA
    {
    private:
        //structure of table
        //from | <to, how>
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> stateMap;
        char current;

        NFA orNFA(NFA& NFA1, NFA& NFA2);
        NFA catNFA(NFA& NFA1, NFA& NFA2);
        NFA plusNFA(NFA& NFA1);
        NFA optNFA(NFA& NFA1);
        NFA anyNFA(NFA& NFA1);
        void add_state(const std::string& name);
        void add_transition(const std::string& from, const std::string& to, const std::string& condition);
        void delete_state(const std::string& name);
        void delete_transition(const std::string& from, const std::string& to);
    public:
        NFA(NFA& NFA1, NFA& NFA2, char op);
        NFA(NFA& NFA1, char op);

    };
}

#endif // AUTOMAT_H
