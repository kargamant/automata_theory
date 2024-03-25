#ifndef AST_H
#define AST_H
#include <string>
#include <memory>

struct Node
{
    private:
        const std::string name;
    public:
        Node(const std::string& name) : name(name) {}
};

struct OrNode : public Node
{
    private:
        std::shared_ptr<Node> lNeighbour;
        std::shared_ptr<Node> rNeighbour;
    public:
        OrNode(const std::string& name);
};

struct ConCatNode: public Node
{
    private:
        std::shared_ptr<Node> lNeighbour;
        std::shared_ptr<Node> rNeighbour;
};

struct PlusNode: public Node
{
    private:
        std::shared_ptr<Node> neighbour;
};

struct OptNode: public Node
{
    private:
    std::shared_ptr<Node> neighbour;
};


#endif // AST_H
