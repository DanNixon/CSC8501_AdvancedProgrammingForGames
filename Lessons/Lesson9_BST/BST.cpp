#include "BST.h"

#include "BSTNode.h"

BST::BST()
  : m_tree(nullptr)
{
}

BST::~BST()
{
  if (m_tree != nullptr)
    delete m_tree;
}

void BST::insert(int value)
{
  // TODO
}

void BST::print(std::ostream & str)
{
  // TODO
}