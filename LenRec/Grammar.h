#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <vector>

#define gEps (Symbol{"__epsilon__"})

struct Symbol;
struct Rule;
class Grammar;


struct Symbol
{
  char* name;
  Symbol();
  Symbol(char* name);
};
struct Rule
{
  Symbol left;
  std::vector<Symbol> right;
};
bool operator==(Symbol s1, Symbol s2);
bool operator!=(Symbol s1, Symbol s2);


class Grammar
{
public:
  std::vector<Symbol> terminals;
  std::vector<Symbol> noTerminals;
  std::vector<Rule> rules;
  Symbol start;
  Grammar(std::vector<Symbol> terminals, std::vector<Symbol> noTerminals, Symbol s, std::vector<Rule> rules);
  Symbol addTerminal(char* name);
  Symbol addNoTerminal(char* name);
  void addRule(Rule rule);
  void addRules(std::vector<Rule> rules);
};








#endif