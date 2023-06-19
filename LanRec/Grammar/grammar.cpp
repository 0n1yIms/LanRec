#include "Grammar.h"
#include <cstring>



Symbol::Symbol()
{
  name = "";
}

Symbol::Symbol(char *name)
{
  this->name = name;  
}


Rule &Rule::operator=(Rule &r)
{
  left = r.left;
  right = r.right;
  return *this;
}


bool operator==(Symbol s1, Symbol s2)
{
  return s1.name == s2.name;
}

bool operator!=(Symbol s1, Symbol s2)
{
  return !(s1 == s2);
}

void Grammar::addTerminal(Symbol s)
{
  terminals.push_back(s);
}
void Grammar::addNoTerminal(Symbol s)
{
  noTerminals.push_back(s);
}
void Grammar::setStart(Symbol s)
{
  start = s;
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
bool Grammar::isTerminal(Symbol s)
{
  for (Symbol t : terminals)
    if (t == s)
      return true;
  return false;
}
bool Grammar::isNoTerminal(Symbol s)
{
  for (Symbol t : noTerminals)
    if (t == s)
      return true;
  return false;
}

