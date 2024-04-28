#include <Regex.h>
#include <Automat.h>
#include <fstream>

int main()
{
    //(ba|b?|in|g+)kd((op?)l(ab(t+k?)cde+}?)p)+k?(ha+lalp?|ha+ram?)?
    //(hal?al|bebra+)Yasos(biba|boba)?
    //minimization monkey examples (aaab?)+, (pok+|pak+)+
    //less monkey example ((uc)?pok+|pak+)+
    std::ifstream fs{"regex_exp.txt"};
    std::ofstream log{"report.txt"};
    std::string expr;
    fs>>expr;
    //std::cout<<expr<<std::endl;
    fs.close();
    Regex::Regex reg;
    reg.compilationWithLogging(expr, log);
    reg.getAutomat().printDot();
    //reg.getAutomat().printAutomat();
    //reg.getAutomat().printDot();

    return 0;
}
