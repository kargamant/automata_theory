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
    //(hal?al|bebra+){0,2}Yasos(biba|boba)? (or Yasos(<biba>biba)|(<boba>boba)
    //sup.&+&|&?(how|what|when){1,3}are(you|they)+
    //omg(you|they)are(so|exteremely){0,5}(fcking)?anno+ying&+?

    //capture groups exp
    //(<aa>a{1,2})?are(<mest>you|they)crazy(<close_remarks>&?+|&+{1,3})
    //What's(<pronoun>your|their)(<number>123|0+|22?8)&?
    //(<name>.+)@(<domen>gmail|mail|yandex)&.(<code>ru|com|org)
    //(<country>&+7|8|&+1|&+375)&((<region>925|375|905)&)(<town>478|312|0{3,3})(<pair>00|11|22|33){2,2}

    //re recovery examples
    //a(bc)?((ck)+|(mk)+)

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

    //to uncomment
    //reg.getAutomat().printDot(portarait_fs);

    std::string result;
    std::unordered_map<std::string, std::string> captures=Regex::re_search(line_expr, result, reg);
    std::cout<<"scanning results:"<<std::endl;
    std::cout<<"recognized sequence: "<<result<<std::endl;
    std::cout<<"captures:"<<std::endl;
    for(auto& cg: captures)
    {
        std::cout<<"<"<<cg.first<<">"<<": "<<cg.second<<std::endl;
    }
    std::cout<<"recovered expression:"<<std::endl;
    std::cout<<Regex::recoverExpr(reg)<<std::endl;

    //Regex::Regex lang1{starEquivalent("0")+"1"+starEquivalent("(0|1)"+starEquivalent("0")+"1")};
    //Regex::Regex lang2{starEquivalent("1")+starEquivalent("0+1+")};
    Regex::Regex lang1{"(om|lol|kek)"}; //(ab|cd)+
    Regex::Regex lang2{"abcd"};
    //((e|k|l|o|m|g){0,1}|(e|k|l|o|m|g)+)
    //to be debugged
    //lang2.compilationWithLogging("a"+starEquivalent("o")+starEquivalent("ba"+starEquivalent("o")+"|t+ca"+starEquivalent("o")), std::cout);
    /*Automat aut1=lang1.getAutomat();
    Automat aut2=lang2.getAutomat();
    aut1.printAutomat();
    aut1.printDot();
    aut2.printAutomat();
    aut2.printDot();*/
    //Regex::Regex diff_re=lang1-lang2;
    //diff_re.getAutomat().printDot(portarait_fs);
    Regex::Regex compliment_1=~lang1;
    compliment_1.getAutomat().printDot(portarait_fs);
    return 0;
}
