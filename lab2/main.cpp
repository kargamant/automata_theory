#include <Regex.h>

int main()
{
    //acd(g|9)*(bo(babi)+|bi(ba)+)
    std::string expr="(ba|b?|in|g+)kd(op?)lp(ha+lalp?|ha+ram?)";
    Regex::Regex reg;
    reg.compile(expr);
    return 0;
}
