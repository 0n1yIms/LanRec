#include "grammarDerivation.h"
#include <iostream>
#include <iomanip>

using namespace GrammarTree;
using namespace std;


struct RuleRunner
{
  Rule rule;
  int index = 0;
  bool finished = false;
  RuleNode node;
  void next()
  {
    index++;
    if (index >= rule.right.size())
      finished = true;
  }
  bool finish()
  {
    return finished;
  }
};

typedef vector<RuleRunner> RuleStack;
typedef pair<RuleStack, Word> RuleDerivation;

void printRuleNode(RuleNode &ruleNode, int space, bool first);

void printRuleNode(RuleNode &ruleNode){
  printRuleNode(ruleNode, 0, true);
}

void printRuleNode(RuleNode &rn, int space = 0, bool first = true)
{
  if (rn.simbol != nullptr)
  {
    if (!first)
      cout << setw(space) << rn.simbol->name << endl;
    else
      cout << rn.simbol->name << endl;
      
  }
  else
  {
    if(first)
      cout << rn.rule->left.name << " -> ";
    else
      cout << setw(space) << rn.rule->left.name << " -> ";

    space += rn.rule->left.name.size() + 5;
    for (int i = 0; i < rn.nodes.size(); i++)
    {
      RuleNode &rnode = rn.nodes.at(i);
      if(i == 0)
        printRuleNode(rnode, space, true);
      else
        printRuleNode(rnode, space, false);
      
    }
    space -= rn.rule->left.name.size() + 5;
  }
}

bool makeDerivation(vector<RuleDerivation> &currentDerivations, int i, Grammar &g)
{
  RuleDerivation &rd = currentDerivations.at(i);
  RuleStack &rs = rd.first;
  Word &w = rd.second;
  RuleRunner &rr = rs.back();

  // check if acepted
  if (rs.size() == 1)
  {
    if (rs.back().finish())
      return true; // acepted
  }

  // check if rule finished
  if (rr.finish())
  {
    RuleNode *node = new RuleNode;
    *node = rr.node;
    node->rule = new Rule;
    *node->rule = rr.rule;
    rs.pop_back();
    rs.back().next();
    rs.back().node.nodes.push_back(*node);
    return false;
  }
  if (w.size() == 0)
  {
    currentDerivations.erase(currentDerivations.begin() + i);
    return false;
  }

  if (g.isTerminal(rr.rule.right.at(rr.index)))
  {
    if (w.at(0) == rr.rule.right.at(rr.index))
    {
      Symbol *newS = new Symbol;
      *newS = rr.rule.right.at(rr.index);
      RuleNode *newRuleNode = new RuleNode{newS};
      rr.node.nodes.push_back(*newRuleNode);

      w.erase(w.begin());
      rr.next();
      return false;
    }
    else
    {
      currentDerivations.erase(currentDerivations.begin() + i);
      return false;
    }
  }
  else // is no terminal
  {
    vector<Rule> avRules;
    for (Rule r : g.rules)
      if (r.left == rr.rule.right.at(rr.index))
        avRules.push_back(r);

    for (Rule r : avRules)
    {
      RuleRunner newRr{r, 0};
      RuleStack newRuleStack = rs;
      // newRuleStack.back().node.nodes.push_back(newRr.node);
      newRuleStack.push_back(newRr);
      currentDerivations.push_back({newRuleStack, w});
    }
    currentDerivations.erase(currentDerivations.begin() + i);
    return false;
  }
}

void derive(Grammar g, Word w, vector<RuleNode> &result)
{
  Symbol init = g.start;
  vector<RuleDerivation> currentDerivations;
  for (int i = 0; i < g.rules.size(); i++)
  {
    if (g.rules.at(i).left != init)
      continue;
    RuleStack rs;
    RuleRunner rr{g.rules.at(i), 0};
    Rule ruleCpy = g.rules.at(i);
    Rule *ruleCpy2 = new Rule;
    *ruleCpy2 = g.rules.at(i);
    rr.node.rule = ruleCpy2;

    rs.push_back(rr);
    currentDerivations.push_back({rs, w});
  }

  bool finishAllRules = false;

  while (!finishAllRules)
  {
    bool areAllRulesFinished = true;

    for (int i = 0; i < currentDerivations.size(); i++)
    {
      bool result = makeDerivation(currentDerivations, i, g);
      if(!result)
        areAllRulesFinished = false;
    }

    if (areAllRulesFinished)
      finishAllRules = true;
  }

  if (currentDerivations.size() != 0)
  {
    //first add complete rules and later not completed rules
    for (int i = 0; i < currentDerivations.size(); i++)
    {
      RuleDerivation &rd = currentDerivations.at(i);
      if(rd.second.size() == 0){
        result.push_back(rd.first.at(0).node);
      }
    }
    
    for (int i = 0; i < currentDerivations.size(); i++)
    {
      RuleDerivation &rd = currentDerivations.at(i);
      RuleNode &rn = currentDerivations.at(i).first.at(0).node;
      if(rd.second.size() != 0)
        result.push_back(rn);
    }
  }
}


/*


void printStack(RuleStack &rs, Word &w, int i)
{
  cout << "  derivation(" << setw(2) << i << "): ";

  for (Symbol &s : w)
    cout << s.name << " ";
  cout << endl;

  cout << "    stack:\n";
  for (RuleRunner &rr : rs)
  {
    cout << setw(16) << rr.rule.left.name << " -> ";
    for (Symbol &s : rr.rule.right)
    {
      cout << s.name << " ";
    }
    cout << " |\n";
  }
  cout << endl;
}

void printDerivations(vector<RuleDerivation> &currentDerivations)
{
  cout << "derivations:\n";
  for (int i = 0; i < currentDerivations.size(); i++)
  {
    printStack(currentDerivations.at(i).first, currentDerivations.at(i).second, i);
  }
}

*/