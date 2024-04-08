#include <Regex.h>
#include <NFA.h>

int main()
{
    //(ba|b?|in|g+)kd((op?)l(ab(t+k?)cde+}?)p)+k?(ha+lalp?|ha+ram?)?
    std::string expr="(ab+|c?)piska(sos|sas)+";
    Regex::Regex reg;
    reg.compile(expr);

    /*
    //tested nfa
    Nfa::NFA nfa1(1, "a");
    Nfa::NFA nfa2(1, "b");
    Nfa::NFA nfa3=Nfa::orNFA(nfa1, nfa2);
    nfa1.printNfa();
    nfa2.printNfa();
    nfa3.printNfa();*/
    return 0;
}
