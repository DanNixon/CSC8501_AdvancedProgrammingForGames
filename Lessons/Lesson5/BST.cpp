#include <sstream>

#include "BST.h"

struct node *bst_gen_new_node(int value);

void bst_insert_int(struct node **tree, int value)
{
  // If there is no root node then add one
  if (*tree == nullptr)
  {
    *tree = bst_gen_new_node(value);
    return;
  }

  // Find the branch this value should be in
  struct node **searchBranch = nullptr;
  if (value < (*tree)->value)
    searchBranch = &((*tree)->left);
  else if (value > (*tree)->value)
    searchBranch = &((*tree)->right);
  else
    return;

  if (*searchBranch == nullptr)
    // If the branch does not exist then add this value as the first node
    *searchBranch = bst_gen_new_node(value);
  else
    // Otherwise search the branch
    bst_insert_int(searchBranch, value);
}

void bst_print_tree(std::ostream &str, struct node **tree, size_t level)
{
  // Generate indentation string
  std::stringstream indentStr;
  for (size_t i = 0; i < level; i++)
    indentStr << "  ";
  const std::string indent = indentStr.str();

  // Output the value of this node
  str << (*tree)->value << '\n';

  // Output the left node
  str << indent << "L: ";
  if ((*tree)->left != nullptr)
  {
    bst_print_tree(str, &(*tree)->left, level + 1);
  }
  else
    str << "NULL\n";

  // Output the right node
  str << indent << "R: ";
  if ((*tree)->right != nullptr)
  {
    bst_print_tree(str, &(*tree)->right, level + 1);
  }
  else
    str << "NULL\n";
}

void bst_release_tree(struct node *tree)
{
  if (tree == nullptr)
    return;

  bst_release_tree(tree->left);
  bst_release_tree(tree->right);

  delete tree;
}

struct node *bst_gen_new_node(int value)
{
  struct node *newNode = new struct node;
  newNode->value = value;
  newNode->left = nullptr;
  newNode->right = nullptr;
  return newNode;
}
