#ifndef AST_H
#define AST_H
#include <string>
#include <memory>
#include <vector>
#include <iostream>

namespace Ast
{

    struct Node
    {
            std::string name;
            std::shared_ptr<Node> lNeighbour;
            std::shared_ptr<Node> rNeighbour;
            Node(const std::string& name="") : name(name) {}
            int printNode(std::ostream& stream=std::cout, int spaces=0);
    };

    class AST
    {
        public:
            std::shared_ptr<Node> root;
            AST() : root(nullptr) {}
            AST(const std::string& name); //to create an ast of single node
            AST(std::shared_ptr<Node> node, AST& ast); //to make an ast
            AST(AST& lAst, AST& rAst, std::shared_ptr<Node> node);
            void print(std::ostream& stream=std::cout);
            ~AST() {}
    };
}
//(a|b)*ck(o9+)

#endif // AST_H
