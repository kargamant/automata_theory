#include <Regex.h>

int main()
{
    //(ba|b?|in|g+)kd((op?)l(ab(t+k?)cde+}?)p)+k?(ha+lalp?|ha+ram?)?
    std::string expr="abobi";
    Regex::Regex reg;
    reg.compile(expr);
    return 0;
}
