#pragma once

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
  int m_value;
  BSTNode *m_left;
  BSTNode *m_right;
};