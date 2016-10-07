#include <sstream>

#include "BST.h"

void bst_insert_int(struct node **tree, int value)
{
  struct node *currentNode = *tree;

  // If there is no node then add one
  if (currentNode == nullptr)
  {
    *tree = new struct node;
    (*tree)->value = value;
    (*tree)->left = nullptr;
    (*tree)->right = nullptr;
    return;
  }

  // Ignore identical values already in tree
  if (currentNode->value == value)
    return;

  // Find the branch this value should be in and search it
  if (value < currentNode->value)
    bst_insert_int(&(currentNode->left), value);
  else
    bst_insert_int(&(currentNode->right), value);
}

void bst_print_tree(std::ostream &str, struct node *tree, size_t level)
{
  // Terminate branch recursion when hit a null leaf
  if (tree == nullptr)
  {
    str << "NULL\n";
    return;
  }

  // Generate indentation string
  std::stringstream indentStr;
  for (size_t i = 0; i < level; i++)
    indentStr << "  ";
  const std::string indent = indentStr.str();

  // Output the value of this node
  str << tree->value << '\n';

  // Output the left node
  str << indent << "L: ";
  bst_print_tree(str, tree->left, level + 1);

  // Output the right node
  str << indent << "R: ";
  bst_print_tree(str, tree->right, level + 1);
}

void bst_release_tree(struct node *tree)
{
  // Terminate branch recursion when hit a null leaf
  if (tree == nullptr)
    return;

  // Release branches
  bst_release_tree(tree->left);
  bst_release_tree(tree->right);

  // Release this node
  delete tree;
}
