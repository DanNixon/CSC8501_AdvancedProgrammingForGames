#pragma once

#include <ostream>

class BSTNode;

class BST
{
public:
  BST();
  virtual ~BST();

  void insert(int value);
  void print(std::ostream &str);

private:
  BSTNode *m_tree;
};