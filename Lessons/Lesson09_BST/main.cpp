#include <iostream>
#include <vector>

#include "BST.h"

int main(void)
{
  BST bst;

  std::vector<int> bstVals = {50, 70, 20, 90, 100, 80, 0, 30, 60, 10};
  for (auto it = bstVals.begin(); it != bstVals.end(); ++it)
    bst.insert(*it);

  bst.print(std::cout);

  std::vector<int> bstSearchVals = {10, 75, -65, 100, 0};
  for (auto it = bstSearchVals.begin(); it != bstSearchVals.end(); ++it)
    std::cout << "Contains " << *it << "? "
              << (bst.search(*it) ? "true" : "false") << '\n';

  return 0;
}
