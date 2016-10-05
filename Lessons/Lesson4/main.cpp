#include <iostream>

void swap(int *a, int *b);
void printEven(int *a, int *end);

int main()
{
  int x = 42;
  int y = 76;
  std::cout << "x=" << x << ", y=" << y << '\n';
  swap(&x, &y);
  std::cout << "x=" << x << ", y=" << y << '\n';

  int v[] = {4, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  printEven(v, v + 11);

  int a = 100;

  std::cout << "Value in memory location a is " << a << "\n";
  std::cout << "Address of (the reference to) memory location a is " << &a
            << "\n";

  int *b = &a;

  std::cout << "Value in memory location pointed to by b is " << *b << "\n";
  std::cout << "Value in memory location b is " << b << "\n";
  std::cout << b << " should be the same as the memory location for a: " << &a
            << '\n';
  std::cout << "b is actually at memory location " << &b << '\n';

  int **c;
  c = &b;

  std::cout << "c is now pointing to what b points to: " << **c << '\n';
  std::cout << "c points to: " << *c << '\n';
  std::cout << "c actually holds the value: " << c << '\n';
  std::cout << c << " is the same value as b's memory location: " << &b << '\n';
  std::cout << "c is actually at memory location " << &c << '\n';
  std::cout << "c is eventually retrieving what is in memory location " << **&c
            << '\n';
  std::cout << "the value of a is in memory location " << &a << '\n';

  return 0;
}

void swap(int *a, int *b)
{
  int t = *b;
  *b = *a;
  *a = t;
}

void printEven(int *a, int *end)
{
  while (a != end)
  {
    if (*a % 2 == 0)
      std::cout << *a << ' ';
    a++;
  }
  std::cout << '\n';
}
