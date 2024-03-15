#ifndef REGEX_H
#define REGEX_H
#include <string>
#include "Automat.h"
#include "TreeLib/BinTree.h"

namespace Regex
{
    class Regex
    {
    private:
        static std::string alphabet;
        std::string expr;
        Automat automat;
        Node* formAst();
    public:
        Regex(std::string& expr) : expr(expr) {}

        void compile();
/*		"[0-9](topG|bottomG)"
    .
        0-9
        |
            topG
            bottomG*/

    };

}

#endif // REGEX_H
