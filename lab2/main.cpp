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
    //sus.clown(1488|228|2004)&+(hype)?&+

    //repetetions tests
    //yes(ab){0,5}.&+
    //(hal?al|bebra+){0,2}Yasos(biba|boba)?
    //sup.&+&|&?(how|what|when){1,3}are(you|they)+
    //omg(you|they)are(so|exteremely){0,5}(fcking)?anno+ying&+?

    //capture groups exp
    //(<aa>a{1,2})?are(<mest>you|they)crazy(<close_remarks>&?+|&+{0,1})
    //What's(<pronoun>your|their)(<number>123|0+|22?8)&?

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
