#include "automatonPushDown.h"
#include <cstring>

using namespace std;

State::State(){
  name = nullptr;
}

State::State(char *name){
  this->name = name;
}

Alphabet::Alphabet(){
  name = nullptr;
}

Alphabet::Alphabet(char *name){
  this->name = name;
}

bool operator==(State s1, State s2)
{
  return strcmp(s1.name, s2.name) == 0;
}
bool operator!=(State s1, State s2)
{
  return !(s1 == s2);
}
bool operator==(Alphabet s1, Alphabet s2)
{
  return strcmp(s1.name, s2.name) == 0;
}
bool operator!=(Alphabet s1, Alphabet s2)
{
  return !(s1 == s2);
}



AutomatonPD::AutomatonPD(std::vector<State> states, 
              std::vector<Alphabet> inputAlphabet, 
              std::vector<Alphabet> stackAlphabet, 
              std::vector<Transition> transitions,
              State initState,
              Alphabet stackFirst,
              std::vector<State> finalStates){
  for(State s : states){
    bool isFinalState = false;
    for(State f : finalStates)
      if(s == f)
        isFinalState = true;
    if(isFinalState)
      this->finalStates.push_back(s);
    else 
      this->states.push_back(s);
  }
  this->inputAlphabet = inputAlphabet;
  this->stackAlphabet = stackAlphabet;
  for (Alphabet a : inputAlphabet)
    this->stackAlphabet.push_back(a);

  /// fix, compare if is in states  
  this->transitions = transitions;
  this->initState = initState;
  this->stackFirst = stackFirst;
  

}



bool AutomatonPD::isFinal(State s)
{
  bool isFinalState = false;
  for (State f : finalStates)
    if (f == s)
      isFinalState = true;

  return isFinalState;
}



vector<Transition> AutomatonPD::getTransitions(State from, Alphabet input, Alphabet stack)
{
  vector<Transition> result;
  for (Transition t : transitions)
  {
    if (t.from == from && t.stack == stack)
    {
      if (t.input == input || t.input == _eps)
        result.push_back(t);
    }
  }
  return result;
}

bool AutomatonPD::testTransition(State q, Transition tr, AWord w, vector<Alphabet> stack)
{
  if (q == tr.from && tr.stack == stack.back())
  {
    if (tr.input != _eps)
    {
      if (tr.input != w.at(0))
        return false;
      else
        w.erase(w.begin());
    }
    stack.pop_back();
    q = tr.to;
    for (int i = tr.out.size() - 1; i >= 0; i--)
    {
      if (tr.out[i] == _eps)
        continue;
      stack.push_back(tr.out[i]);
    }
    if (w.size() == 0 && isFinal(q) && stack.size() == 0)
      return true;
    if (w.size() == 0 && stack.size() == 0)
      return false;
    Alphabet a;
    if(w.size() == 0)
      a = _eps;
    else
      a = w.at(0);
    vector<Transition> transitionsAvailable = getTransitions(q, a, stack.back());

    for (Transition t : transitionsAvailable)
    {
      if (testTransition(q, t, w, stack))
        return true;
    }
  }
  return false;
}


bool AutomatonPD::run(AWord w)
{
  for(Alphabet a : w){
    if(a == _eps)
      return false;
    bool isInputAlphabet = true;
    for (Alphabet b : stackAlphabet)
      if (a == b)
        isInputAlphabet = false;

    if (!isInputAlphabet)
      return false;
  }

  vector<Alphabet> stack;
  stack.push_back(stackFirst);

  vector<Transition> transitions = getTransitions(initState, w[0], stack.back());

  for (Transition tr : transitions)
  {
    if (testTransition(initState, tr, w, stack))
      return true;
  }
  return false;

}










