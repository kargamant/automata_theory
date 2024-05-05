#include <AST.h>

namespace Ast
{

    AST::AST(const std::string& name) : root(new Node(name))
    {
    }

    AST::AST(std::shared_ptr<Node> node, AST& ast) : root(node)
    {
        root->lNeighbour=ast.root;
        root->capture_name=node->capture_name;
    }

    AST::AST(AST& lAst, AST& rAst, std::shared_ptr<Node> node) : root(node)
    {
        root->lNeighbour=lAst.root;
        //lAst.root->capture_name=node->capture_name;
        root->rNeighbour=rAst.root;
        //rAst.root->capture_name=node->capture_name;
    }

    int Node::printNode(std::ostream& stream, int spaces)
    {
        if(capture_name.empty()) stream<<std::string(spaces, ' ')<<name<<std::endl;
        else stream<<std::string(spaces, ' ')<<name<<" <"<<capture_name<<">"<<std::endl;
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
