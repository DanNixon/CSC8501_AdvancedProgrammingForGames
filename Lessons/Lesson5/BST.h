#pragma once

#include <functional>
#include <ostream>

struct node
{
  int value;
  struct node *left;
  struct node *right;
};

void bst_insert_int(struct node **tree, int value);
void bst_print_tree(std::ostream &str, node *tree, size_t level = 0);
void bst_release_tree(struct node *tree);
size_t bst_depth(struct node *tree, std::function<size_t(size_t, size_t)> f);
