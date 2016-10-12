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
  if (m_tree == nullptr)
  {
    m_tree = new BSTNode(value);
    return;
  }

  m_tree->insert(value);
}

void BST::print(std::ostream &str)
{
  if (m_tree != nullptr)
    m_tree->print(str, 0);
  else
    str << "Empty tree";
}

bool BST::search(int value)
{
  if (m_tree == nullptr)
    return false;

  return m_tree->search(value);
}