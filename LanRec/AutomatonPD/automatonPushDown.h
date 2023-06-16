#ifndef AUTOMATONPUSHDOWN_H
#define AUTOMATONPUSHDOWN_H

#include <vector>

#define _eps (Alphabet{"__epsilon__"})

struct State;
struct Alphabet;
struct Transition;
class AutomatonPD;



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

typedef std::vector<Alphabet> Word;

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
  bool testTransition(State q, Transition tr, Word w, std::vector<Alphabet> stack);

  bool isFinal(State state);

public:
  /// @brief Construct a new AutomatonPD object
  /// @param states 
  /// @param inputAlphabet 
  /// @param stackAlphabet 
  /// @param transitions 
  /// @param initState 
  /// @param stackFirst 
  /// @param finalStates 
  AutomatonPD(std::vector<State> states, 
              std::vector<Alphabet> inputAlphabet, 
              std::vector<Alphabet> stackAlphabet, 
              std::vector<Transition> transitions,
              State initState,
              Alphabet stackFirst,
              std::vector<State> finalStates);
  bool AutomatonPD::run(Word w);

};


bool operator==(State a, State b);
bool operator!=(State a, State b);
bool operator==(Alphabet a, Alphabet b);
bool operator!=(Alphabet a, Alphabet b);

// Word getWord(char* word);


#endif // AUTOMATONPUSHDOWN_H