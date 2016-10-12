#pragma once

#include <ostream>

class BSTNode
{
public:
  BSTNode(int value);
  virtual ~BSTNode();

  inline int value() const
  {
    return m_value;
  }

  bool search(int value);

private:
  friend class BST;
  void insert(int value);
  void print(std::ostream &stream, size_t level);

private:
  int m_value;
  BSTNode *m_left;
  BSTNode *m_right;
};