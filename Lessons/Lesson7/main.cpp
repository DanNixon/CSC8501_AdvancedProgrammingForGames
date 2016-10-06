#include <iostream>

void swap(int x, int y)
{
  int temp = x;
  x = y;
  y = temp;
}

void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

void swap_ref(int &x, int &y)
{
  int temp = x;
  x = y;
  y = temp;
}

int main()
{
  int a, b;

  std::cout << "Please type in a number\n";
  std::cin >> a;
  std::cout << "Please type in another number\n";
  std::cin >> b;

  std::cout << "before swap, a = " << a << " and b = " << b << '\n';
  swap(a, b);
  std::cout << "after swap (by value), a = " << a << " and b = " << b << '\n';
  swap(&a, &b);
  std::cout << "after swap by pointer reference, a = " << a << " and b = " << b
            << '\n';

  swap_ref(a, b);
  std::cout << "after swap using references, a = " << a << " and b = " << b
            << '\n';

  int &a_ref = a;

  return 0;
}
