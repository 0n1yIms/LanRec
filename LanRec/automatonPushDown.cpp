#include "automatonPushDown.h"

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


void AutomatonPD::addState(State q)
{
  states.push_back(q);
}

void AutomatonPD::addFinalState(State q)
{
  finalStates.push_back(q);
}

bool AutomatonPD::isFinal(State s)
{
  bool isFinalState = false;
  for (State f : finalStates)
    if (f == s)
      isFinalState = true;

  return isFinalState;
}

void AutomatonPD::addInputAlphabet(Alphabet a)
{
  inputAlphabet.push_back(a);
  stackAlphabet.push_back(a);
}

void AutomatonPD::addStackAlphabet(Alphabet a)
{
  stackAlphabet.push_back(a);
}

/// fix, compare if is in states
void AutomatonPD::addTransitions(std::vector<Transition> transitions)
{
  for (Transition t : transitions)
  {
    this->transitions.push_back(t);
  }
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

bool AutomatonPD::testTransition(State q, Transition tr, Word w, vector<Alphabet> stack)
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

bool AutomatonPD::run(State init, Alphabet stackFrst, Word w)
{
  for(Alphabet a : w){
    if(a == _eps)
      return false;
    bool isInputAlphabet = false;
    for (Alphabet b : inputAlphabet)
      if (a == b)
        return true;

    if (!isInputAlphabet)
      return false;
  }

  vector<Alphabet> stack;
  stack.push_back(stackFrst);

  vector<Transition> transitions = getTransitions(init, w[0], stack.back());

  for (Transition tr : transitions)
  {
    if (testTransition(init, tr, w, stack))
      return true;
  }
  return false;

  // if(currentState == 1 && stack.back() == _epsilon){
  // std::cout << "Cadena aceptada" << std::endl;
  // }else{
  // std::cout << "Cadena no aceptada" << std::endl;
  // }
}


/*
Word getWord(char *w){
  Word word;
  for(int i = 0; i < strlen(w); i++){
    string s(1, w[i]);
    new char[]
    Alphabet a{};
    word.push_back(a);
  }
  return word;
}
*/


