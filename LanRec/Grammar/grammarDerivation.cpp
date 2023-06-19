#include "grammarDerivation.h"
#include <iostream>
#include <iomanip>

using namespace GrammarTree;
using namespace std;

struct RuleNode
{
  Symbol *simbol = nullptr;
  vector<RuleNode> nodes;
};

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

bool makeDerivation(RuleDerivation &rd)
{
  RuleStack &rs = rd.first;
  Word &w = rd.second;
  
  if (rs.size() == 1)   //finished rule 
  {
    if (rs.back().finish())
      // acepted
      return true;
  }
  RuleRunner &rr = rs.back();
  
  if (rr.finish())
  {
    rs.pop_back();
    if (rs.size() != 0)
      rs.back().next();
    continue;
  }
  if (w.size() == 0)
  {
    return false;
  }

  Symbol &s = rr.rule.right.at(rr.index);

  if (g.isTerminal(s))
  {
    if (w.at(0) == s)
    {
      w.erase(w.begin());
      rr.next();
      rr.node.nodes.push_back(RuleNode{&s, {}});
      continue;
    }
    else
    {
      crtRules.erase(crtRules.begin() + i);
      continue;
    }
  }
  else
  {
    vector<Rule> avRules;
    for (Rule r : g.rules)
      if (r.left == s)
        avRules.push_back(r);

    for (Rule r : avRules)
    {
      RuleRunner newRr{r, 0};
      RuleStack newRuleStack = rs;
      newRuleStack.back().node.nodes.push_back(newRr.node);
      newRuleStack.push_back(newRr);
      crtRules.push_back({newRuleStack, w});
    }
    crtRules.erase(crtRules.begin() + i);
    continue;
  }
}


bool derive(Grammar g, Symbol r, Word w)
{
  vector<RuleDerivation> crtRules;
  for (int i = 0; i < g.rules.size(); i++)
  {
    if (g.rules.at(i).left != r)
      continue;
    RuleStack rs;
    RuleRunner rr{g.rules.at(i), 0};

    rs.push_back(rr);
    crtRules.push_back({rs, w});
  }

  bool finishAllRules = false;
  // add initial rule

  while (!finishAllRules)
  {
    bool areAllRulesFinished = true;
    for (RuleDerivation &rd : crtRules)
    {
      if (rd.first.size() == 1)
      {
        if (rd.first.back().finish())
        {
          areAllRulesFinished = false;
          break;
        }
      }
    }
    if (areAllRulesFinished)
    {
      finishAllRules = true;
      continue;
    }

    /*// cout rules;
    // cout << "crtRules:\n";
    // for (RuleDerivation &rd : crtRules)
    // {
    //   cout << "rule:\n";
    //   RuleStack &rs = rd.first;
    //   cout << "      ruleStack:\n";
    //   for (RuleRunner &rr : rs)
    //   {
    //     cout << setw(16) << rr.rule.left.name << " -> ";
    //     for (Symbol &s : rr.rule.right)
    //     {
    //       cout << s.name << " ";
    //     }
    //     cout << " |\n";
    //   }
    //   cout << "      word: ";
    //   for (Symbol n : rd.second)
    //   {
    //     cout << n.name << " ";
    //   }

    // }
    // cout << endl;*/

    for (int i = 0; i < crtRules.size(); i++)
    {
      RuleDerivation &rd = crtRules.at(i);
      RuleStack &rs = rd.first;
      Word &w = rd.second;
      if (rs.size() == 1)
      {
        if (rs.back().finish())
          // acepted
          continue;
      }
      // RuleRunner &rr = rs.first.back();
      RuleRunner &rr = rs.back();
      if (rr.finish())
      {
        rs.pop_back();
        if (rs.size() != 0)
          rs.back().next();
        continue;
      }
      if (w.size() == 0)
      {
        crtRules.erase(crtRules.begin() + i);
        continue;
      }

      Symbol &s = rr.rule.right.at(rr.index);

      if (g.isTerminal(s))
      {
        if (w.at(0) == s)
        {
          w.erase(w.begin());
          rr.next();
          rr.node.nodes.push_back(RuleNode{&s});
          continue;
        }
        else
        {
          crtRules.erase(crtRules.begin() + i);
          continue;
        }
      }
      else
      {
        vector<Rule> avRules;
        for (Rule r : g.rules)
          if (r.left == s)
            avRules.push_back(r);

        for (Rule r : avRules)
        {
          RuleRunner newRr{r, 0};
          RuleStack newRuleStack = rs;
          newRuleStack.back().node.nodes.push_back(newRr.node);
          newRuleStack.push_back(newRr);
          crtRules.push_back({newRuleStack, w});
        }
        crtRules.erase(crtRules.begin() + i);
        continue;
      }
    }
  }
  if (crtRules.size() == 0)
    return false;
  else
    return true;
}

bool derive(Grammar grammar, Word input) // init
{
  bool der = derive(grammar, grammar.start, input);
  return der;
}

// S -> a S b | a b

// aaabbb

//