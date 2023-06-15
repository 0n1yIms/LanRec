#include "Grammar.h"

Symbol::Symbol()
{
  name = nullptr;
}

Symbol::Symbol(char *name)
{
  this->name = name;
}

bool operator==(Symbol s1, Symbol s2)
{
  return strcmp(s1.name, s2.name) == 0;
}

bool operator!=(Symbol s1, Symbol s2)
{
  return !(s1 == s2);
}

Grammar::Grammar(std::vector<Symbol> terminals, 
                 std::vector<Symbol> noTerminals, 
                 Symbol s, 
                 std::vector<Rule> rules)
{
  this->terminals = terminals;
  this->noTerminals = noTerminals;
  this->rules = rules;
  this->start = s;
}


Symbol Grammar::addTerminal(char *name)
{
  Symbol s{name};
  terminals.push_back(s);
  return s;
}
Symbol Grammar::addNoTerminal(char *name)
{
  Symbol s{name};
  noTerminals.push_back(s);
  return s;
}

void Grammar::addRule(Rule rule)
{
  rules.push_back(rule);
}

void Grammar::addRules(std::vector<Rule> rules)
{
  for (Rule r : rules)
    addRule(r);
}


