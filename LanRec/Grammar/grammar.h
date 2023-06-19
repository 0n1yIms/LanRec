#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <vector>
#include <string>

#define gEps (Symbol{"__epsilon__"})


struct Symbol;
struct Rule;
class Grammar;
typedef std::vector<Symbol> Word;


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
  void addTerminal(Symbol s);
  void addNoTerminal(Symbol s);
  void setStart(Symbol s);

  void addRule(Rule rule);
  void addRules(std::vector<Rule> rules);

  bool isTerminal(Symbol s);
  bool isNoTerminal(Symbol s);
};




inline Rule cvtRule(char* a, char* b){
  Rule r;
  std::string s = "";
  for (int i = 0; i < strlen(a); i++){
    if (a[i] != ' ')
      s += a[i];
  }
  while (b[0] == ' ' && strlen(b) > 0)
    b++;
  s = "";
  for (int i = 0; i < strlen(b); i++)
  {
    if(b[i] != ' ')
      s += b[i];
    else {
      r.right.push_back(Symbol{(char*)s.c_str()});
      s = "";
    }
  }
  
  return r;
}



#endif