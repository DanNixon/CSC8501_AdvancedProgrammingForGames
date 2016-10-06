#include <iostream>

int global_variable = 50;

void some_function()
{
  int a = 400;
  char letter = 'b';
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

  std::cout << "the value in a is " << a << '\n';

  std::cout << "the value pointed to by 'b' is " << *b << '\n';
  delete b;
  b = nullptr;

  std::cout << "output some data\n";

  some_function();

  return 0;
}
