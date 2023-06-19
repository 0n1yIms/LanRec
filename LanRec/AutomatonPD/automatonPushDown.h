#ifndef AUTOMATONPUSHDOWN_H
#define AUTOMATONPUSHDOWN_H

#include <vector>
#include <Grammar/grammar.h>

#define _eps (Alphabet{"__epsilon__"})

struct State;
struct Alphabet;
struct Transition;
class AutomatonPD;

typedef std::vector<Alphabet> AWord;


struct State
{
  char* name;
  State();
  State(char* name);
};

struct Alphabet
{
  char* name;
  Alphabet();
  Alphabet(char* name);
};

struct Transition {
  State from;
  State to;
  Alphabet input;
  Alphabet stack;
  std::vector<Alphabet> out;
};


class AutomatonPD
{
private:
  std::vector<Transition> transitions;

  std::vector<State> states;
  std::vector<State> finalStates;
  std::vector<Alphabet> stackAlphabet;
  std::vector<Alphabet> inputAlphabet;
  State initState;
  Alphabet stackFirst;

  std::vector<Transition> getTransitions(State from, Alphabet input, Alphabet stack);
  bool testTransition(State q, Transition tr, AWord w, std::vector<Alphabet> stack);

  bool isFinal(State state);

public:
  AutomatonPD(std::vector<State> states, 
              std::vector<Alphabet> inputAlphabet, 
              std::vector<Alphabet> stackAlphabet, 
              std::vector<Transition> transitions,
              State initState,
              Alphabet stackFirst,
              std::vector<State> finalStates);
  bool run(AWord w);
};


bool operator==(State a, State b);
bool operator!=(State a, State b);
bool operator==(Alphabet a, Alphabet b);
bool operator!=(Alphabet a, Alphabet b);

// Word getWord(char* word);


#endif // AUTOMATONPUSHDOWN_H