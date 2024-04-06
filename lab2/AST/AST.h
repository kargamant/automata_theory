#ifndef AST_H
#define AST_H
#include <string>
#include <memory>
#include <vector>

struct Node
{
        const std::string name;
        std::shared_ptr<Node> lNeighbour;
        std::shared_ptr<Node> rNeighbour;
        Node(const std::string& name="") : name(name) {}
};

class AST
{
    private:
        std::shared_ptr<Node> root;
    public:
        AST(const std::string& name); //to create an ast of single node
        AST(std::shared_ptr<Node> node, AST& ast); //to make an ast
        AST(AST& lAst, AST& rAst, std::shared_ptr<Node> node);
};
//(a|b)*ck(o9+)

#endif // AST_H