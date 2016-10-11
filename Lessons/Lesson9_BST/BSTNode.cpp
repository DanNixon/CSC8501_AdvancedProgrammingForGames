#include "BSTNode.h"

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
  return false;
}
