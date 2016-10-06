#include <sstream>

#include "BST.h"

//#define BST_RECURSIVE

struct node *bst_gen_new_node(int value);

#ifdef BST_RECURSIVE
void bst_insert_int(struct node **tree, int value)
{
  struct node *currentNode = *tree;

  // If there is no root node then add one
  if (currentNode == nullptr)
  {
    *tree = bst_gen_new_node(value);
    return;
  }

  // Ignore identical values already in tree
  if (currentNode->value == value)
    return;

  // Find the branch this value should be in
  struct node **searchBranch = nullptr;
  if (value < currentNode->value)
    searchBranch = &(currentNode->left);
  else
    searchBranch = &(currentNode->right);

  if (*searchBranch == nullptr)
    // If the branch does not exist then add this value as the first node
    *searchBranch = bst_gen_new_node(value);
  else
    // Otherwise search the branch
    bst_insert_int(searchBranch, value);
}
#else
void bst_insert_int(struct node **tree, int value)
{
  struct node *currentNode = *tree;

  // If there is no root node then add one
  if (currentNode == nullptr)
  {
    *tree = bst_gen_new_node(value);
    return;
  }

  while (currentNode != nullptr)
  {
    if (value < currentNode->value)
    {
      // If at leaf add new node
      if (currentNode->left == nullptr)
      {
        currentNode->left = bst_gen_new_node(value);

        // Mark termination
        currentNode = nullptr;
      }
      else
        // Otherwise search branch
        currentNode = currentNode->left;
    }
    else
    {
      // If at leaf add new node
      if (currentNode->right == nullptr)
      {
        currentNode->right = bst_gen_new_node(value);

        // Mark termination
        currentNode = nullptr;
      }
      else
        // Otherwise search branch
        currentNode = currentNode->right;
    }
  }
}
#endif

void bst_print_tree(std::ostream &str, struct node **tree, size_t level)
{
  // Terminate branch recursion when hit a null leaf
  if (*tree == nullptr)
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
  str << (*tree)->value << '\n';

  // Output the left node
  str << indent << "L: ";
  bst_print_tree(str, &(*tree)->left, level + 1);

  // Output the right node
  str << indent << "R: ";
  bst_print_tree(str, &(*tree)->right, level + 1);
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

struct node *bst_gen_new_node(int value)
{
  struct node *newNode = new struct node;
  newNode->value = value;
  newNode->left = nullptr;
  newNode->right = nullptr;
  return newNode;
}
