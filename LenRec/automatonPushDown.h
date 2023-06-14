#ifndef AUTOMATONPUSHDOWN_H
#define AUTOMATONPUSHDOWN_H

#include <vector>

#define _epsilon -2

class AutomatonPD;
typedef int State;
typedef int SigmaT;
typedef int SigmaN;
typedef int Alphabet;

struct Transition {
  State from;
  State to;
  SigmaT input;
  SigmaN stack;
  std::vector<Alphabet> output;
};


class AutomatonPD
{
private:
  std::vector<Transition> transitions;
  int states = -1;
  int terminals = -1;
  int noTerminals = -1;
public:
  State addState();
  SigmaT addSigmaTerminal();
  SigmaN addSigmaNoTerminal();

  void addTransitions(std::vector<Transition> transitions);

  void run(char* input);

};

















#endif // AUTOMATONPUSHDOWN_H