#ifndef REGEX_H
#define REGEX_H
#include <string>
//#include "Automat.h"
#include <AST.h>
#include <Automat.h>
using namespace Ast;
using namespace Automato;

namespace Regex
{
    AST formAst(const std::string& expr);
    Automat formNfa(AST& ast, int id);
    Automat formDfa(Automat& nfa);
    std::pair<int, int> findClosestBrackets(std::vector<AST>& asts);
    void bracketsPairToAst(std::pair<int, int>& closest_pair, std::vector<AST>& asts);
    void concatAsts(std::vector<AST>& asts);
    class Regex
    {
    private:
        static std::string alphabet;
        std::string ex;
        Automat automat;

        bool isLetter(char c) {return (c>=97 && c<=122) || (c>=65 && c<=90);}
    public:
        Regex() : ex("") {}
        Regex(const std::string& expr);
        Regex(Automat&& aut) : automat(aut) {}

        Regex operator~();
        Automat getAutomat() {return automat;}
        friend Regex operator-(Regex& re1, Regex& re2);
        void compile(const std::string& expr);
        void compilationWithLogging(const std::string& expr, std::ostream& stream);
        friend std::unordered_map<std::string, std::string> re_search(const std::string& str, std::string& result, Regex& re);
        friend std::string recoverExpr(Regex& re);
    };

    std::unordered_map<std::string, std::string> re_search(const std::string& str, std::string& result, Regex& re);
    std::string recoverExpr(Regex& re);
    Regex operator-(Regex& re1, Regex& re2);
}

#endif // REGEX_H
