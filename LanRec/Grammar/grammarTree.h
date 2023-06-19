#ifndef GRAMMAR_TREE_H
#define GRAMMAR_TREE_H

#include "grammar.h"
#include <vector>

namespace GrammarTree
{
  class Node;
  class BranchNode;
  class LeafNode;

  typedef BranchNode RootNode;

  class Node
  {
  public:
    static const int BRANCH = 0;
    static const int LEAF = 1;

  protected:
    int type;
    Node(int type);

  public:
    Symbol symbol;
    std::vector<Node> children;
  };

  class BranchNode : public Node
  {
  public:
    BranchNode(std::vector<Node> children);
    std::vector<Node> getChildren();
  };

  class LeafNode : public Node
  {
  public:
    LeafNode(Symbol symbol);
    Symbol getSymbol();
  };

};

#endif // !GRAMMAR_TREE_H