#include <iostream>
#include <vector>
#include <ctime>

#include "BST.h"

#define TYPE int

BST<TYPE> *gBST = nullptr;

void insert_func(TYPE value)
{
  std::this_thread::sleep_for(std::chrono::milliseconds(std::rand() % 25));
  gBST->insert(value);
}

int main(void)
{
  std::srand((unsigned int) std::time(0));

  gBST = new BST<TYPE>();

  std::vector<TYPE> bstVals = {50, 70, 20, 90, 100, 80, 0, 30, 60, 10};
  std::vector<std::thread> threads;

  for (auto it = bstVals.begin(); it != bstVals.end(); ++it)
    threads.push_back(std::thread(insert_func, *it));

  for (auto it = threads.begin(); it != threads.end(); ++it)
    it->join();

  gBST->print(std::cout);

  std::vector<TYPE> bstSearchVals = {10, 75, -65, 100, 0};
  for (auto it = bstSearchVals.begin(); it != bstSearchVals.end(); ++it)
    std::cout << "Contains " << *it << "? "
              << (gBST->search(*it) ? "true" : "false") << '\n';

  delete gBST;
  gBST = nullptr;

  return 0;
}
