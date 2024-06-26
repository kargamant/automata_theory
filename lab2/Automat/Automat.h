#ifndef AUTOMAT_H
#define AUTOMAT_H
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <StateSet.h>
#include <State.h>
#include <unordered_set>

namespace Automato
{
    struct StateHash
    {
        std::size_t operator()(const State& key) const
        {
            return std::hash<int>()(key.id);
        }
    };

    struct StateEqual
    {
        bool operator()(const State& key1, const State& key2) const
        {
            return (key1.id == key2.id) && (key1.type==key2.type);
        }
    };

    struct unorderedSetHash
    {
        std::size_t operator()(const std::unordered_set<int>& key) const
        {
            return std::hash<int>()(*key.begin())+(*key.begin())%73;
        }
    };

    class Automat
    {
    private:
        static std::unordered_map<std::string, bool> transitions_sieve;

        //structure of table
        //from | <to, vector<how>>
        std::unordered_map<int, std::unordered_map<int, std::unordered_map<std::string, bool>>> stateMap;
        std::unordered_set<int> current;
        std::unordered_set<int> accepting;
        std::unordered_map<std::string, std::unordered_set<int>> capture_groups;
        std::unordered_map<int, std::unordered_set<std::string>> search_capture_map;

        int start;
        int end;
        int id;

        void add_state(int id);
        void add_transition(int from, int to, const std::string& condition);
        void delete_state(int id);
        //void delete_transition(const std::string& from, const std::string& to, int i);
        void delete_transition(int from, int to, const std::string& condition);

        static void activate_transitions_sieve();
    public:
        static const std::string alphabet;
        Automat() : id(-1) {}
        Automat(int id, const std::string& transition);
        Automat(Automat& Automat1);
        Automat(Automat&& Automat1);
        //Automat(Automat& Automat1, Automat& Automat2, char op);
        //Automat(Automat& Automat1, char op);
        std::unordered_map<int, std::unordered_map<int, std::unordered_map<std::string, bool>>> getMap() {return stateMap;}
        //std::string getStart() {return "start_"+std::to_string(id);}
        //std::string getEnd() {return "end_"+std::to_string(id);}
        void fill_search_capture_map();
        void add_capture_state(int id, const std::string& capture_name);
        void add_capture_all_states(const std::string& capture_name);
        int getId() {return id;}
        void printAutomat(std::ostream& stream=std::cout);
        void printDot(std::ostream& stream=std::cout);
        std::unordered_map<std::string, std::string> verifyStr(const std::string& str, std::string& result, bool isNfa=false);
        std::string recoverRe();
        std::string fillTransitions(int from, int to);

        Automat& operator=(Automat&& automat);
        Automat& operator<<(Automat& automat);
        //Automat& operator+=(Automat& automat);

        friend Automat orAutomat(Automat& Automat1, Automat& Automat2);
        friend Automat catAutomat(Automat& Automat1, Automat& Automat2);
        friend Automat plusAutomat(Automat& Automat1);
        friend Automat optAutomat(Automat& Automat1);
        friend Automat anyAutomat(int id);
        friend Automat nfaToDfa(Automat& automat);
        friend StateSet formStateSet(Automat& automat, const StateSet& stateSet, const std::string& transition, bool isNfa);
        friend Automat minimizeDfa(Automat& dfa);
        friend Automat rangeAutomat(Automat& automat, int min, int max);
        friend Automat productDfa(Automat& dfa1, Automat& dfa2);
        friend Automat differenceDfa(Automat& dfa1, Automat& dfa2);
        friend Automat complimentDfa(Automat& dfa);
    };
    Automat rangeAutomat(Automat& automat, int min, int max);
    Automat orAutomat(Automat& Automat1, Automat& Automat2);
    Automat catAutomat(Automat& Automat1, Automat& Automat2);
    Automat plusAutomat(Automat& Automat1);
    Automat optAutomat(Automat& Automat1);
    Automat anyAutomat(int id);
    Automat nfaToDfa(Automat& automat);
    Automat minimizeDfa(Automat& dfa);
    StateSet formStateSet(Automat& automat, const StateSet& stateSet, const std::string& transition, bool isNfa=true);
    std::string starEquivalent(const std::string& node);
    std::string postfixString(const std::string& str, const std::string& postfix);
    std::string orString(const std::string& str1, const std::string& str2);
    Automat productDfa(Automat& dfa1, Automat& dfa2);
    Automat differenceDfa(Automat& dfa1, Automat& dfa2);
    Automat complimentDfa(Automat& dfa);
}

#endif // AUTOMAT_H
