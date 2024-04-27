#include <Regex.h>
#include <Automat.h>
#include <fstream>

int main()
{
    //(ba|b?|in|g+)kd((op?)l(ab(t+k?)cde+}?)p)+k?(ha+lalp?|ha+ram?)?
    //minimization exp (brat|bro+)abc
    std::ifstream fs{"regex_exp.txt"};
    std::string expr;
    std::getline(fs, expr);
    Regex::Regex reg;
    reg.compile(expr);
    //reg.getAutomat().printAutomat();
    //reg.getAutomat().printDot();

    return 0;
}
