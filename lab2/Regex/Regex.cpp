#include <Regex.h>
#include <iostream>
#include <limits>
#include <stack>
#include <chrono>

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
            //std::cout<<"node name: "<<node_name<<std::endl;
            asts.emplace_back(node_name);
        }

        //where do we start
        /*for(auto& ast: asts)
        {
            std::cout<<"ast:"<<std::endl;
            ast.print();
            std::cout<<std::endl;
        }*/

        while(start_elements!=0)
        {
            std::pair<int, int> closest_pair=findClosestBrackets(asts);

            bracketsPairToAst(closest_pair, asts);

            //std::cout<<closest_pair.first<<" "<<closest_pair.second<<" "<<asts.size()<<std::endl;
            asts.erase(asts.begin()+closest_pair.second);
            asts.erase(asts.begin()+closest_pair.first);
            start_elements--;

        }

        /*std::cout<<"brackets parced:"<<std::endl;
        for(auto& ast: asts)
        {
            std::cout<<"ast:"<<std::endl;
            ast.print();
            std::cout<<std::endl;
        }*/

        std::pair<int, int> expr_boundaries={0, asts.size()};
        bracketsPairToAst(expr_boundaries, asts);
        concatAsts(asts);

        /*std::cout<<"end check"<<std::endl;
        for(auto& ast: asts)
        {
            std::cout<<"ast:"<<std::endl;
            ast.print();
            std::cout<<std::endl;
        }*/
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
           //asts[i].print();
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
        //std::cout<<closest_pair.first<<" "<<closest_pair.second<<" "<<asts.size()<<std::endl;
        //if(closest_pair.first==0 && closest_pair.second==asts.size()) i--;
        while((closest_pair.second-closest_pair.first)!=2 && i<closest_pair.second)
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
        if(asts.size()!=1 && asts.size()!=closest_pair.second)
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

    Automat formNfa(AST& ast, int id)
    {
        //std::cout<<"rec ast:"<<std::endl;
        //ast.print();
        if(ast.root->lNeighbour==nullptr && ast.root->rNeighbour==nullptr)
        {
            //std::cout<<"leaf_"<<ast.root->name<<std::endl;
            Automat automat=Automat(id, ast.root->name);
            //automat.printAutomat();
            //std::cout<<"root name: \""<<ast.root->name<<"\""<<std::endl;
            return automat;
        }

        Automat nfa1;
        Automat nfa2;
        if(ast.root->lNeighbour!=nullptr)
        {
            AST l_ast;
            l_ast.root=ast.root->lNeighbour;
            nfa1=formNfa(l_ast, id+1);
        }

        if(ast.root->rNeighbour!=nullptr)
        {
            AST r_ast;
            r_ast.root=ast.root->rNeighbour;
            nfa2=formNfa(r_ast, nfa1.getId()+1);
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
                //if(ast.root->rNeighbour->name.empty())
                Automat automat=catAutomat(nfa1, nfa2);
                //automat.printAutomat();
                return automat;
            }
        }


    }

    void Regex::compile(const std::string& expr)
    {
        AST ast=formAst(expr);
        //ast.print();

        Automat nfa=formNfa(ast, 1);
        //nfa.printAutomat();

        Automat dfa=nfaToDfa(nfa);
        //dfa.printDot();
        //dfa.printAutomat();
        Automat minDfa=minimizeDfa(dfa);
        automat=std::move(minDfa);
    }

    void Regex::compilationWithLogging(const std::string& expr, std::ostream& stream)
    {
        double sum_time=0;

        auto start=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        AST ast=formAst(expr);
        auto finish=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        sum_time+=finish.count()-start.count();
        stream<<std::endl<<"AST built in "<<finish.count()-start.count()<<" milliseconds"<<std::endl;
        ast.print(stream);
        stream<<std::string(100, '-')<<std::endl;

        start=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        Automat nfa=formNfa(ast, 1);
        finish=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        sum_time+=finish.count()-start.count();
        stream<<std::endl<<"NFA built in "<<finish.count()-start.count()<<" milliseconds"<<std::endl;
        nfa.printAutomat(stream);
        nfa.printDot(stream);
        stream<<std::string(100, '-')<<std::endl;

        start=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        Automat dfa=nfaToDfa(nfa);
        finish=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        sum_time+=finish.count()-start.count();
        stream<<std::endl<<"DFA built in "<<finish.count()-start.count()<<" milliseconds"<<std::endl;
        dfa.printAutomat(stream);
        dfa.printDot(stream);
        stream<<std::string(100, '-')<<std::endl;

        start=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        Automat minDfa=minimizeDfa(dfa);
        finish=std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        sum_time+=finish.count()-start.count();
        stream<<std::endl<<"DFA minimized in "<<finish.count()-start.count()<<" milliseconds"<<std::endl;
        minDfa.printAutomat(stream);
        minDfa.printDot(stream);
        stream<<std::string(100, '-')<<std::endl;

        stream<<"Total time: "<<sum_time<<" milliseconds"<<std::endl;
        automat=std::move(minDfa);

    }
}
