#include <Regex.h>
#include <NFA.h>

int main()
{
    //(ba|b?|in|g+)kd((op?)l(ab(t+k?)cde+}?)p)+k?(ha+lalp?|ha+ram?)?
    std::string expr="abobi";
    Regex::Regex reg;
    reg.compile(expr);

    /*
    tested nfa
    Nfa::NFA nfa1(1, "a");
    Nfa::NFA nfa2(2, "b");
    Nfa::NFA nfa3=Nfa::orNFA(nfa1, nfa2);

    Nfa::NFA nfa4=Nfa::plusNFA(nfa3);
    Nfa::NFA nfa5=Nfa::optNFA(nfa4);
    Nfa::NFA nfa6=Nfa::NFA(6, "k");
    Nfa::NFA nfa7=Nfa::catNFA(nfa6, nfa5);
    nfa7.printNfa();*/
    return 0;
}
