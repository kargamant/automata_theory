#include <Regex.h>
#include <iostream>
#include <limits>
#include <stack>

namespace Regex
{
    std::string Regex::alphabet="|+?.";
    AST formAst(const std::string& expr)
    {
        int start_elements=0;
        std::vector<AST> asts;
        for(int i=0; i<expr.size(); i++)
        {
            if(expr[i]=='(') start_elements++;
            std::string node_name{expr[i]};
            asts.emplace_back(node_name);
        }

        //where do we start
        for(auto& ast: asts)
        {
            std::cout<<"ast:"<<std::endl;
            ast.print();
            std::cout<<std::endl;
        }

        while(start_elements!=0)
        {
            std::pair<int, int> closest_pair=findClosestBrackets(asts);

            bracketsPairToAst(closest_pair, asts);

            asts.erase(asts.begin()+closest_pair.first);
            asts.erase(asts.begin()+closest_pair.second-1);
            start_elements--;

        }

        std::cout<<"brackets parced:"<<std::endl;
        for(auto& ast: asts)
        {
            std::cout<<"ast:"<<std::endl;
            ast.print();
            std::cout<<std::endl;
        }

        std::pair<int, int> expr_boundaries={0, asts.size()};
        bracketsPairToAst(expr_boundaries, asts);
        concatAsts(asts);

        std::cout<<"end check"<<std::endl;
        for(auto& ast: asts)
        {
            std::cout<<"ast:"<<std::endl;
            ast.print();
            std::cout<<std::endl;
        }
        //std::cout<<"borders: "<<closest_pair.first<<" "<<closest_pair.second<<std::endl;
        //std::cout<<"distance: "<<(closest_pair.second-closest_pair.first)<<std::endl;


        return asts[0];
    }
    std::pair<int, int> findClosestBrackets(std::vector<AST>& asts)
    {
       std::stack<int> open_indicies;
       std::pair<int, int> closest_pair={0, std::numeric_limits<int>::max()};
       for(int i=0; i<asts.size(); i++)
       {
           if(asts[i].root->name=="(")
           {
               open_indicies.push(i);
           }
           else if(asts[i].root->name==")")
           {
               int open=open_indicies.top();
               if((i-open)<(closest_pair.second-closest_pair.first))
               {
                   closest_pair.first=open;
                   closest_pair.second=i;
               }
           }
       }
       return closest_pair;
    }

    void bracketsPairToAst(std::pair<int, int>& closest_pair, std::vector<AST>& asts)
    {

        //looking for + or ?
        for(int i=closest_pair.first+1; i<closest_pair.second; i++)
        {
            if(asts[i].root->name=="+" || asts[i].root->name=="?")
            {
                AST new_ast=AST(asts[i].root, asts[i-1]);
                asts.erase(asts.begin()+i-1);
                closest_pair.second-=1;
                asts[i-1]=new_ast;
            }
            /*std::cout<<"+?iter check"<<std::endl;
            for(auto& ast: asts)
            {
                std::cout<<"ast:"<<std::endl;
                ast.print();
                std::cout<<std::endl;
            }*/
        }

        //concatinating ~
        int i=closest_pair.first+2;
        while((closest_pair.second-closest_pair.first)!=2 && (i-closest_pair.first)<(closest_pair.second-closest_pair.first))
        {
            if(asts[i].root->name!="|" && asts[i-1].root->name!="|")
            {
                AST new_ast=AST(asts[i-1], asts[i], std::shared_ptr<Node>(new Node("~")));
                asts.erase(asts.begin()+i-1);
                closest_pair.second-=1;
                asts[i-1]=new_ast;
            }
            else i++;
        }

        if(asts.size()!=1)
        {
            //operation |
            for(int i=closest_pair.first+1; i<closest_pair.second; i++)
            {
                if(asts[i].root->name=="|")
                {
                    AST new_ast=AST(asts[i-1], asts[i+1], std::shared_ptr<Node>(new Node("|")));
                    asts.erase(asts.begin()+i-1);
                    asts.erase(asts.begin()+i-1);
                    closest_pair.second-=2;
                    asts[i-1]=new_ast;
                    i--;
                }
            }
        }
    }


    void concatAsts(std::vector<AST>& asts)
    {
        while(asts.size()!=1)
        {
            AST new_ast=AST(asts[0], asts[1], std::shared_ptr<Node>(new Node("~")));
            asts.erase(asts.begin());
            asts[0]=new_ast;
        }
    }

    Automat formAutomat(AST& ast, int id)
    {
        //std::cout<<"rec ast:"<<std::endl;
        //ast.print();
        if(ast.root->lNeighbour==nullptr && ast.root->rNeighbour==nullptr)
        {
            //std::cout<<"leaf_"<<ast.root->name<<std::endl;
            Automat automat=Automat(id, ast.root->name);
            //automat.printAutomat();
            return automat;
        }

        Automat nfa1;
        Automat nfa2;
        if(ast.root->lNeighbour!=nullptr)
        {
            AST l_ast;
            l_ast.root=ast.root->lNeighbour;
            nfa1=formAutomat(l_ast, id+1);
        }

        if(ast.root->rNeighbour!=nullptr)
        {
            AST r_ast;
            r_ast.root=ast.root->rNeighbour;
            nfa2=formAutomat(r_ast, nfa1.getId()+1);
        }

        if(ast.root->lNeighbour==nullptr)
        {
            if(ast.root->name=="+")
            {
                //std::cout<<"+right_neighbour_"<<ast.root->rNeighbour->name<<std::endl;
                Automat automat=plusAutomat(nfa2);
                //automat.printAutomat();
                return automat;
            }
            else if(ast.root->name=="?")
            {
                //std::cout<<"?right_neighbour_"<<ast.root->rNeighbour->name<<std::endl;
                Automat automat=optAutomat(nfa2);
                //automat.printAutomat();
                return automat;
            }
        }
        else if(ast.root->rNeighbour==nullptr)
        {
            if(ast.root->name=="+")
            {
                //std::cout<<"+left_neighbour_"<<ast.root->lNeighbour->name<<std::endl;
                Automat automat=plusAutomat(nfa1);
                //automat.printAutomat();
                return automat;
            }
            else if(ast.root->name=="?")
            {
                //std::cout<<"?left_neighbour_"<<ast.root->lNeighbour->name<<std::endl;
                Automat automat=optAutomat(nfa1);
                //automat.printAutomat();
                return automat;
            }
        }
        else
        {
            if(ast.root->name=="|")
            {
                //std::cout<<ast.root->lNeighbour->name<<" | "<<ast.root->rNeighbour->name<<std::endl;
                Automat automat=orAutomat(nfa1, nfa2);
                //automat.printAutomat();
                return automat;
            }
            else if(ast.root->name=="~")
            {
                //std::cout<<ast.root->lNeighbour->name<<" ~ "<<ast.root->rNeighbour->name<<std::endl;
                Automat automat=catAutomat(nfa1, nfa2);
                //automat.printAutomat();
                return automat;
            }
        }


    }

    void Regex::compile(const std::string& expr)
    {
        AST ast=formAst(expr);
        Automat automat=formAutomat(ast, 1);
        automat.printAutomat();
    }
}
