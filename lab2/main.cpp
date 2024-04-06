#include <Regex.h>

int main()
{
    std::string expr="acd(g|9)*(bo(babi)+|bi(ba)+)";
    Regex::Regex reg;
    reg.compile(expr);
    return 0;
}
