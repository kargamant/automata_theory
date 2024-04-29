#include <Regex.h>
#include <Automat.h>
#include <fstream>

int main()
{
    //funny exp lol
    //(ba|b?|in|g+)kd((op?)l(ab(t+k?)cde+}?)p)+k?(ha+lalp?|ha+ram?)?
    //(hal?al|bebra+)Yasos(biba|boba)?
    //minimization monkey examples (aaab?)+, (pok+|pak+)+
    //less monkey example ((uc)?pok+|pak+)+
    //(tatu|bi2|sector(gaza)?)(coo+l|no+rm|meh)&?
    //Jasper(Cu+min|Coo+min|Ma?glot)

    //needed files
    std::ifstream re_fs{"regex_exp.txt"};
    std::ofstream log{"report.txt"};
    std::ifstream line_fs{"line.txt"};
    std::ofstream portarait_fs{"automato.dot"};

    std::string line_expr;
    std::string re_expr;
    re_fs>>re_expr;
    line_fs>>line_expr;

    Regex::Regex reg;
    reg.compilationWithLogging(re_expr, log);

    reg.getAutomat().printDot(portarait_fs);

    std::string result;
    bool isValid=Regex::re_search(line_expr, result, reg);
    std::cout<<"scanning results:"<<std::endl;
    std::cout<<"recognized sequence: "<<result<<std::endl;
    std::cout<<"is Valid: "<<isValid<<std::endl;


    return 0;
}
