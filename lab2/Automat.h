#ifndef AUTOMAT_H
#define AUTOMAT_H
#include <unordered_map>
#include "State.h"

namespace Regex
{
    class Automat
    {
    private:
        std::unordered_map<char, std::unordered_map<char, char>> stateMap;
        char current;
    public:
        Automat() {}
        //Automat(Node* root);

    };
}

#endif // AUTOMAT_H
