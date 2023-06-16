#include "grammar.h"
#include "automatonPushDown.h"




inline AutomatonPD grammarToAutomaton(Grammar g){
  AutomatonPD a;
  State q0("q0");
  State q1("q1");
  State q2("q2");
  a.addState(q0);
  a.addState(q1);
  a.addFinalState(q2);

  for (Symbol t : g.terminals)
    a.addInputAlphabet(t.name);
  
  for (Symbol nt : g.noTerminals)
    a.addStackAlphabet(nt.name);

  Alphabet Z0("Z0");
  a.addStackAlphabet(Z0);

  Alphabet init;
  init.name = g.start.name;

  Transition t0{q0, q1, _eps, Z0, {init, Z0}};
  Transition tF{q1, q2, _eps, Z0, {_eps}};

  a.addTransitions({t0, tF});

  for (Rule r : g.rules){
    std::vector<Alphabet> stack;
    for (Symbol s : r.right){
      if(s == gEps)
        stack.push_back(_eps);
      else
        stack.push_back({s.name});
    }

    Transition t{q1, q1, _eps, {r.left.name}, stack};
    a.addTransitions({t});
  }

  for (Symbol t : g.terminals){
    Transition tran{q1, q1, {t.name}, {t.name}, {_eps}};
    a.addTransitions({tran});
  }

  return a;
}