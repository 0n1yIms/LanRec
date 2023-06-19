#include "grammarTree.h"

using namespace GrammarTree;

Node::Node(int type)
{
  this->type = type;
}

BranchNode::BranchNode(std::vector<Node> children) : Node(Node::BRANCH)
{
  this->children = children;
}

std::vector<Node> BranchNode::getChildren()
{
  return children;
}

LeafNode::LeafNode(Symbol symbol) : Node(Node::LEAF)
{
  this->symbol = symbol;
}

Symbol LeafNode::getSymbol()
{
  return symbol;
}

