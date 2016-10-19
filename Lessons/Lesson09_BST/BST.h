#pragma once

#include <mutex>
#include <ostream>

#include "BSTNode.h"

template <typename T> class BST
{
public:
  BST()
      : m_mutex()
      , m_tree(nullptr)
  {
  }

  virtual ~BST()
  {
    if (m_tree != nullptr)
      delete m_tree;
  }

  void insert(T value)
  {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_tree == nullptr)
    {
      m_tree = new BSTNode<T>(value);
      return;
    }

    m_tree->insert(value);
  }

  void print(std::ostream &str)
  {
    if (m_tree != nullptr)
      m_tree->print(str, 0);
    else
      str << "Empty tree";
  }

  bool search(T value)
  {
    if (m_tree == nullptr)
      return false;

    return m_tree->search(value);
  }

private:
  std::mutex m_mutex;
  BSTNode<T> *m_tree;
};
