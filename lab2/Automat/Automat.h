#ifndef AUTOMAT_H
#define AUTOMAT_H
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <StateSet.h>
#include <State.h>
#include <Transition.h>
#include <memory>

namespace Automato
{
    struct StateHash
    {
        std::size_t operator()(const State& key) const
        {
            return std::hash<std::string>()(key.name);
        }
    };

    struct nonConstStateHash
    {
        std::size_t operator()(State& key)
        {
            return std::hash<std::string>()(key.name);
        }
    };
    struct StateEqual
    {
        bool operator()(const State& key1, const State& key2) const
        {
            return (key1.name == key2.name);
        }
    };

    struct nonConstStateEqual
    {
        bool operator()(State& key1, State& key2)
        {
            return (key1.name == key2.name);
        }
    };
    class Automat
    {
    private:
        static const std::string alphabet;
        //structure of table
        //from | <to, vector<how>>
        std::unordered_map<State, std::unordered_map<State, std::vector<Transition>, StateHash, StateEqual>, StateHash, StateEqual> stateMap;
        std::vector<State> current;
        std::shared_ptr<State> start;
        std::shared_ptr<State> end;
        int id;

        void add_state(const std::string& name);
        void add_transition(const std::string& from, const std::string& to, const std::string& condition);
        void delete_state(const std::string& name);
        void delete_transition(const std::string& from, const std::string& to, int i);
        void delete_transition(const std::string& from, const std::string& to, const std::string& condition);
    public:
        Automat() : id(-1) {}
        Automat(int id, const std::string& transition);
        Automat(Automat& Automat1);
        Automat(Automat&& Automat1);
        //Automat(Automat& Automat1, Automat& Automat2, char op);
        //Automat(Automat& Automat1, char op);

        std::string getStart() {return "start_"+std::to_string(id);}
        std::string getEnd() {return "end_"+std::to_string(id);}
        int getId() {return id;}
        void printAutomat(std::ostream& stream=std::cout);
        void printDot(std::ostream& stream=std::cout);

        Automat& operator=(Automat&& automat);
        Automat& operator<<(Automat& automat);

        friend Automat orAutomat(Automat& Automat1, Automat& Automat2);
        friend Automat catAutomat(Automat& Automat1, Automat& Automat2);
        friend Automat plusAutomat(Automat& Automat1);
        friend Automat optAutomat(Automat& Automat1);
        friend Automat anyAutomat(int id);
        friend Automat nfaToDfa(Automat& automat);
        friend StateSet formStateSet(Automat& automat, const StateSet& stateSet, const std::string& transition);
    };
    Automat orAutomat(Automat& Automat1, Automat& Automat2);
    Automat catAutomat(Automat& Automat1, Automat& Automat2);
    Automat plusAutomat(Automat& Automat1);
    Automat optAutomat(Automat& Automat1);
    Automat anyAutomat(int id);
    Automat nfaToDfa(Automat& automat);
    StateSet formStateSet(Automat& automat, const StateSet& stateSet, const std::string& transition);
}

#endif // AUTOMAT_H
