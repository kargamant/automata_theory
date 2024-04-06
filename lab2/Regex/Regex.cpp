#include <Regex.h>
#include <iostream>
#include <limits>
#include <stack>

namespace Regex
{
    std::string Regex::alphabet="|+?.";
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
        std::vector<AST> asts;
        for(int i=closest_pair.first+1; i<closest_pair.second; i++)
        {
            std::string node_name{expr[i]};
            asts.emplace_back(node_name);
        }

        //looking for + or ?
        for(int i=1; i<asts.size(); i++)
        {
            if(asts[i].root->name=="+" || asts[i].root->name=="?")
            {
                AST new_ast=AST(asts[i].root, asts[i-1]);
                asts.erase(asts.begin()+i-1);
                asts[i-1]=new_ast;
            }
        }

        //concatinating ~
        int i=1;
        while(asts.size()!=1 && i<asts.size())
        {
            if(asts[i].root->name!="|" && asts[i-1].root->name!="|")
            {
                AST new_ast=AST(asts[i-1], asts[i], std::shared_ptr<Node>(new Node("~")));
                asts.erase(asts.begin()+i-1);
                asts[i-1]=new_ast;
            }
            else i++;
        }

        if(asts.size()!=1)
        {
            //operation |
            for(int i=0; i<asts.size(); i++)
            {
                if(asts[i].root->name=="|")
                {
                    AST new_ast=AST(asts[i-1], asts[i+1], std::shared_ptr<Node>(new Node("|")));
                    asts.erase(asts.begin()+i-1);
                    asts.erase(asts.begin()+i-1);
                    asts[i-1]=new_ast;
                    i--;
                }
            }
        }

        //check
        for(auto& ast: asts)
        {
            std::cout<<"ast:"<<std::endl;
            ast.print();
            std::cout<<std::endl;
        }
        //std::cout<<"borders: "<<closest_pair.first<<" "<<closest_pair.second<<std::endl;
        //std::cout<<"distance: "<<(closest_pair.second-closest_pair.first)<<std::endl;


        return AST("a");
    }
    void Regex::compile(const std::string& expr)
    {
        formAst(expr);
    }
}
