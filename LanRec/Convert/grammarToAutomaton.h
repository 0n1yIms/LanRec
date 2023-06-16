#include <Grammar/grammar.h>
#include <AutomatonPD/automatonPushDown.h>

#include <vector>


inline AutomatonPD grammarToAutomaton(Grammar g){
  State q0("q0");
  State q1("q1");
  State q2("q2");
  
  std::vector<Alphabet> inputAlphabet;
  std::vector<Alphabet> stackAlphabet;
  for (Symbol t : g.terminals)
    inputAlphabet.push_back({t.name});
  
  for (Symbol nt : g.noTerminals)
    stackAlphabet.push_back({nt.name});

  Alphabet Z0("Z0");
  stackAlphabet.push_back(Z0);

  Alphabet init;
  init.name = g.start.name;


  std::vector<Transition> transitions;
  Transition t0{q0, q1, _eps, Z0, {init, Z0}};
  Transition tF{q1, q2, _eps, Z0, {_eps}};

  transitions.push_back(t0);
  transitions.push_back(tF);

  for (Rule r : g.rules){
    std::vector<Alphabet> stack;
    for (Symbol s : r.right){
      if(s == gEps)
        stack.push_back(_eps);
      else
        stack.push_back({s.name});
    }

    Transition t{q1, q1, _eps, {r.left.name}, stack};
    transitions.push_back(t);
  }

  for (Symbol t : g.terminals){
    Transition tran{q1, q1, {t.name}, {t.name}, {_eps}};
    transitions.push_back(tran);
  }

  AutomatonPD automatonPD(
    {q0, q1, q2},
    inputAlphabet,
    stackAlphabet,
    transitions,
    q0,
    Z0,
    {q2}
  );

  return automatonPD;
}