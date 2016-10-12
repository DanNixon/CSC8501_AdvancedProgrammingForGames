#include "BSTNode.h"

#include <sstream>

BSTNode::BSTNode(int value)
    : m_value(value)
    , m_left(nullptr)
    , m_right(nullptr)
{
}

BSTNode::~BSTNode()
{
  if (m_left != nullptr)
    delete m_left;

  if (m_right != nullptr)
    delete m_right;
}

bool BSTNode::search(int value)
{
  if (value == m_value)
    return true;

  if (value < m_value && m_left != nullptr)
    return m_left->search(value);

  if (value > m_value && m_right != nullptr)
    return m_right->search(value);

  return false;
}

void BSTNode::insert(int value)
{
  if (value == m_value)
    return;

  BSTNode ** node = &m_left;
  if (value > m_value)
    node = &m_right;

  if (*node != nullptr)
    (*node)->insert(value);
  else
    *node = new BSTNode(value);
}

void BSTNode::print(std::ostream &stream, size_t level)
{
  // Generate indentation string
  std::stringstream indentStr;
  for (size_t i = 0; i < level; i++)
    indentStr << "  ";
  const std::string indent = indentStr.str();

  // Output the value of this node
  stream << m_value << '\n';

  // Output the left node
  stream << indent << "L: ";
  if (m_left != nullptr)
    m_left->print(stream, level + 1);
  else
    stream << "null\n";

  // Output the right node
  stream << indent << "R: ";
  if (m_right != nullptr)
    m_right->print(stream, level + 1);
  else
    stream << "null\n";
}
