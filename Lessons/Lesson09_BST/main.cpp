#include <iostream>
#include <vector>

#include "BST.h"

#define TYPE int

int main(void)
{
  BST<TYPE> *bst = new BST<TYPE>();

  std::vector<TYPE> bstVals = {50, 70, 20, 90, 100, 80, 0, 30, 60, 10};

  for (auto it = bstVals.begin(); it != bstVals.end(); ++it)
    bst->insert(*it);

  bst->print(std::cout);

  std::vector<TYPE> bstSearchVals = {10, 75, -65, 100, 0};
  for (auto it = bstSearchVals.begin(); it != bstSearchVals.end(); ++it)
    std::cout << "Contains " << *it << "? "
              << (bst->search(*it) ? "true" : "false") << '\n';

  delete bst;
  bst = nullptr;

  return 0;
}
