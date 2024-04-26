#ifndef AUTOMAT_H
#define AUTOMAT_H
#include <unordered_map>
#include <string>
#include <iostream>
#include <set>
#include <vector>

namespace Automato
{
    class Automat
    {
    private:
        static const std::string alphabet;
        //structure of table
        //from | <to, vector<how>>
        std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> stateMap;
        std::vector<std::string> current;
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

        Automat& operator=(Automat&& automat);
        Automat& operator<<(Automat& automat);

        friend Automat orAutomat(Automat& Automat1, Automat& Automat2);
        friend Automat catAutomat(Automat& Automat1, Automat& Automat2);
        friend Automat plusAutomat(Automat& Automat1);
        friend Automat optAutomat(Automat& Automat1);
        friend Automat anyAutomat(int id);
        friend Automat nfaToDfa(Automat& automat);
        friend std::set<std::string> formStateSet(Automat& automat, const std::set<std::string>& stateSet, const std::string& transition);
    };
    Automat orAutomat(Automat& Automat1, Automat& Automat2);
    Automat catAutomat(Automat& Automat1, Automat& Automat2);
    Automat plusAutomat(Automat& Automat1);
    Automat optAutomat(Automat& Automat1);
    Automat anyAutomat(int id);
    Automat nfaToDfa(Automat& automat);
    std::set<std::string> formStateSet(Automat& automat, const std::set<std::string>& stateSet, const std::string& transition);
}

#endif // AUTOMAT_H
