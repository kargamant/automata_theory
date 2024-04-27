#include <Regex.h>
#include <Automat.h>

int main()
{
    //(ba|b?|in|g+)kd((op?)l(ab(t+k?)cde+}?)p)+k?(ha+lalp?|ha+ram?)?
    std::string expr="(brat|bro+)";
    Regex::Regex reg;
    reg.compile(expr);
    reg.getAutomat().printAutomat();
    reg.getAutomat().printDot();

    return 0;
}
