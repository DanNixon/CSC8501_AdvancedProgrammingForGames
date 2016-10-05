#include <iostream>
#include <string>
#include <vector>

#include "BST.h"

int main()
{
  struct node *tree = nullptr;
  std::vector<int> bstVals = {5, 7, 2, 5, 8, 9, 2, 3, 5, 3};

  for (auto it = bstVals.begin(); it != bstVals.end(); ++it)
    bst_insert_int(&tree, *it);

  bst_print_tree(std::cout, &tree);
  bst_release_tree(tree);

  char c;
  std::string *s;

  c = 't';
  s = new std::string("abcd");

  std::cout << "c = " << c << "\ns = " << *s << '\n';

  int *arr = new int[10];

  for (size_t i = 0; i < 10; i++)
    arr[i] = i * i;

  int *p = arr;
  while (p != arr + 10)
    std::cout << *(p++) << ' ';

  delete[] arr;

  return 0;
}
