#include <iostream>

int main()
{
  int a;
  int *b;

  a = 100;
  b = new int;

  std::cout << "The pointer b points to the memory address " << b
            << " located on the heap\n";
  std::cout << "The value in memory location b is " << *b << '\n';

  *b = a;

  std::cout << "The value of stack variable a is " << a << '\n';
  std::cout << "The 'heap' memory pointed to by b contains " << *b << '\n';

  delete b;
  b = nullptr;

  return 0;
}
