#include <AST.h>

AST::AST(const std::string& name) : root(new Node(name))
{
}

AST::AST(std::shared_ptr<Node> node, AST& ast) : root(node)
{
    root->lNeighbour=ast.root;
}

AST::AST(AST& lAst, AST& rAst, std::shared_ptr<Node> node) : root(node)
{
    root->lNeighbour=lAst.root;
    root->rNeighbour=rAst.root;
}
