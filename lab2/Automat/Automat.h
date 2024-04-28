#ifndef AUTOMAT_H
#define AUTOMAT_H
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <StateSet.h>
#include <State.h>

namespace Automato
{
    class Automat
    {
    private:
        static const std::string alphabet;
        //structure of table
        //from | <to, vector<how>>
        std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> stateMap;
        std::set<std::string> current;
        std::set<std::string> accepting;
        std::string start;
        std::string end;
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
        bool verifyStr(const std::string& str, std::string& result, bool isNfa=false);

        Automat& operator=(Automat&& automat);
        Automat& operator<<(Automat& automat);

        friend Automat orAutomat(Automat& Automat1, Automat& Automat2);
        friend Automat catAutomat(Automat& Automat1, Automat& Automat2);
        friend Automat plusAutomat(Automat& Automat1);
        friend Automat optAutomat(Automat& Automat1);
        friend Automat anyAutomat(int id);
        friend Automat nfaToDfa(Automat& automat);
        friend StateSet formStateSet(Automat& automat, const StateSet& stateSet, const std::string& transition, bool isNfa);
        friend Automat minimizeDfa(Automat& dfa);
    };
    Automat orAutomat(Automat& Automat1, Automat& Automat2);
    Automat catAutomat(Automat& Automat1, Automat& Automat2);
    Automat plusAutomat(Automat& Automat1);
    Automat optAutomat(Automat& Automat1);
    Automat anyAutomat(int id);
    Automat nfaToDfa(Automat& automat);
    Automat minimizeDfa(Automat& dfa);
    StateSet formStateSet(Automat& automat, const StateSet& stateSet, const std::string& transition, bool isNfa=true);
}

#endif // AUTOMAT_H
