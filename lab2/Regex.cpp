#include "Regex.h"

namespace Regex
{
    std::string Regex::alphabet="|";
    Node* Regex::formAst()
    {
        //let's make a concat node parcing
        Node* op=initNode();
        Node* olderOp=initNode();
        op->info=expr[0];
        for(int i=1; i<expr.length(); i++)
        {


        }

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

    }
}
