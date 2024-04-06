#include <Regex.h>
#include <iostream>
#include <limits>
#include <stack>

namespace Regex
{
    //std::string Regex::alphabet="|";
    AST Regex::formAst(const std::string& expr)
    {
        std::stack<int> open_indicies;
        std::pair<int, int> closest_pair={0, std::numeric_limits<int>::max()};
        for(int i=0; i<expr.length(); i++)
        {
            if(expr[i]=='(')
            {
                open_indicies.push(i);
            }
            else if(expr[i]==')')
            {
                int open=open_indicies.top();
                if((i-open)<(closest_pair.second-closest_pair.first))
                {
                    closest_pair.first=open;
                    closest_pair.second=i;
                }
            }
        }
        std::cout<<"borders: "<<closest_pair.first<<" "<<closest_pair.second<<std::endl;
        std::cout<<"distance: "<<(closest_pair.second-closest_pair.first)<<std::endl;
        /*
        //Number one algo
        int oldLBracket=0;
        int lBracket=0;
        int rBracket=0;
        int distance=std::numeric_limits<int>::max();
        int counter=0;
        for(int i=0; i<expr.length(); i++)
        {
            if(counter!=0 && expr[i]!=')') counter++;
            else if(expr[i]==')')
            {
                counter--;
                if(counter<distance)
                {
                    rBracket=i;
                    distance=counter;
                }
                else
                {
                    lBracket=oldLBracket;
                }
            }

            if(expr[i]=='(')
            {
                counter=0;
                counter++;
                oldLBracket=lBracket;
                lBracket=i;
            }
        }

        std::cout<<"borders: "<<lBracket<<" "<<rBracket<<std::endl;
        std::cout<<"distance: "<<distance<<std::endl;
        return AST("a");
        */
        /*
        for(int i=lBrackets+1; i<rBrackets; i++)
        {
            if(isLetter(expr[i]))
            {
                if(ast.isEmpty())
                {
                    std::shared_ptr<Node> aNode=std::make_shared<Node>(new Node(std::to_string(expr[i])));
                    ast.insert(aNode);
                }
                else
                {
                    std::shared_ptr<Node> aNode=std::make_shared<Node>(new Node(std::to_string(expr[i])));
                    std::shared_ptr<Node> catNode=std::make_shared<Node>(new Node("."));
                    ast.insert(catNode);
                    ast.insert(aNode);
                }
            }

        }

        for(int i=lBrackets+1; i<rBrackets; i++)
        {
            if(expr[i])
        }*/
        /*Node* root=initNode();
        //for now just expressions like a|b, then I'll make it more complicated
        std::string leftOp, rightOp;
        std::string& op=leftOp;
        for(int i=0; i<expr.length(); i++)
        {
            if(expr[i]=="|")
            {
                op=rightOp;
                continue;
            }
            op+=expr[i];
        }
        Node* left=initNode();
        Node* right=initNode();*/
        return AST("a");
    }
    void Regex::compile(const std::string& expr)
    {
        formAst(expr);
    }
}
