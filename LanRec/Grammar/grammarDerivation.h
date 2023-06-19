#ifndef GRAMMAR_DERIVATION_H
#define GRAMMAR_DERIVATION_H


#include "grammar.h"
#include "grammarTree.h"
#include <vector>


struct RuleNode
{
  Symbol *simbol = nullptr;
  Rule *rule = nullptr;
  std::vector<RuleNode> nodes;
};

void printRuleNode(RuleNode &ruleNode);

void derive(Grammar g, Word w, std::vector<RuleNode> &result);










#endif // !GRAMMAR_DERIVATION_H