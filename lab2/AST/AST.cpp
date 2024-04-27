#include <AST.h>

namespace Ast
{

    AST::AST(const std::string& name) : root(new Node(name))
    {
        if(name.empty())
        {
            root=nullptr;
        }
    }

    AST::AST(std::shared_ptr<Node> node, AST& ast) : root(node)
    {
        if(!ast.root->name.empty()) root->lNeighbour=ast.root;
        else root->lNeighbour=nullptr;
    }

    AST::AST(AST& lAst, AST& rAst, std::shared_ptr<Node> node) : root(node)
    {
        if(!lAst.root->name.empty()) root->lNeighbour=lAst.root;
        else root->lNeighbour=nullptr;
        if(!rAst.root->name.empty()) root->rNeighbour=rAst.root;
        else root->rNeighbour=nullptr;
    }

    int Node::printNode(std::ostream& stream, int spaces)
    {
        stream<<std::string(spaces, ' ')<<name<<std::endl;
        if(lNeighbour!=nullptr)
        {
            lNeighbour->printNode(stream, spaces+4);
        }
        if(rNeighbour!=nullptr)
        {
            rNeighbour->printNode(stream, spaces+4);
        }
        return 0;
    }

    void AST::print(std::ostream& stream)
    {
        root->printNode(stream);
    }
}
