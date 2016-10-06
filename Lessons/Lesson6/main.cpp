#include <iostream>
#include <string>

int global_variable = 50;

namespace some_namespace
{
void some_function()
{
  int a = 400;
  char letter = 'b';
  std::cout << "some_namespace::some_function()\n";
}
}

namespace some_other_namespace
{
void some_function()
{
  int a = 400;
  char letter = 'b';
  std::cout << "some_other_namespace::some_function()\n";
}
}

int main()
{
  std::cout << "global variable contains the value " << global_variable << '\n';

  int a = 100;
  int *b;

  {
    int a = 200;

    std::cout << "the value in a is " << a << '\n';

    int *local_ptr = new int(300);

    b = local_ptr;
  }

  int v = 1;
  std::cout << "v = " << v << '\n';

  {
    int v = 2;
    std::cout << "v = " << v << '\n';
  }

  {
    int v = 3;
    std::cout << "v = " << v << '\n';
  }

  std::cout << "v = " << v << '\n';

  std::cout << "the value in a is " << a << '\n';
  std::cout << "the value pointed to by 'b' is " << *b << '\n';

  delete b;
  b = nullptr;

  some_namespace::some_function();
  some_other_namespace::some_function();

  return 0;
}
