#include <iostream>
#include <string>
#include <vector>
#include <random>

#include "BST.h"

#define PROFILE

int main()
{
  struct node *tree = nullptr;

#ifdef PROFILE
  for (size_t i = 0; i < 100000; i++)
    bst_insert_int(&tree, std::rand());
#else
  std::vector<int> bstVals = {50, 70, 20, 90, 100, 80, 0, 30, 60, 10};
  for (auto it = bstVals.begin(); it != bstVals.end(); ++it)
    bst_insert_int(&tree, *it);
#endif

#ifndef PROFILE
  bst_print_tree(std::cout, tree);
#endif

  bst_release_tree(tree);

#if 0
  char c;
  std::string *s;

  c = 't';
  s = new std::string("abcd");

  std::cout << "c = " << c << "\ns = " << *s << '\n';

  int *arr = new int[10];

  for (size_t i = 0; i < 10; i++)
    arr[i] = (int) i * (int) i;

  int *p = arr;
  while (p != arr + 10)
    std::cout << *(p++) << ' ';

  delete[] arr;
#endif

  return 0;
}
