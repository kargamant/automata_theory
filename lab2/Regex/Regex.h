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
    Automat formAutomat(AST& ast, int id);
    std::pair<int, int> findClosestBrackets(std::vector<AST>& asts);
    void bracketsPairToAst(std::pair<int, int>& closest_pair, std::vector<AST>& asts);
    void concatAsts(std::vector<AST>& asts);
    class Regex
    {
    private:
        static std::string alphabet;
        std::string ex;
        //Automat automat;

        bool isLetter(char c) {return (c>=97 && c<=122) || (c>=65 && c<=90);}
    public:
        Regex() : ex("") {}
        Regex(const std::string& expr);

        void compile(const std::string& expr);

    };

}

#endif // REGEX_H
