#include <iostream>

int nums[] = {7, 3, 5, 2, 1, 4, 6, 9, 10, 9};

void swap(int x, int y);
void swap(int *x, int *y);
void swap_ref(int &x, int &y);
void swap_chars(char &x, char &y);
void sort(int *begin, int *end);
void printIntArray(int *begin, int *end);

int main()
{
  printIntArray(nums, nums + 10);
  sort(nums, nums + 10);
  printIntArray(nums, nums + 10);

  int a = 12;
  int b = 24;
  std::cout << "a = " << a << ", b = " << b << '\n';

  swap(a, b);
  std::cout << "a = " << a << ", b = " << b << '\n';

  swap(&a, &b);
  std::cout << "a = " << a << ", b = " << b << '\n';

  swap_ref(a, b);
  std::cout << "a = " << a << ", b = " << b << '\n';

  char c = 'y';
  char d = 'n';
  std::cout << "c = " << c << ", d = " << d << '\n';

  swap_chars(c, d);
  std::cout << "c = " << c << ", d = " << d << '\n';

  int x = 3;
  int y = 4;
  int &xr = x;
  xr = y;
  std::cout << "xr = " << xr << '\n';

  return 0;
}

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

void swap_chars(char &x, char &y)
{
  char &temp = y;
  y = x;
  x = temp;
}

// Bubble sort
void sort(int *begin, int *end)
{
  bool haveSwapped;
  do
  {
    haveSwapped = false;
    int *i = begin;
    while (i < end - 1)
    {
      if (*i > *(i + 1))
      {
        swap_ref(*i, *(i + 1));
        haveSwapped = true;
      }

      i++;
    }
  } while (haveSwapped);
}

void printIntArray(int *begin, int *end)
{
  while (begin != end)
    std::cout << *(begin++) << ' ';

  std::cout << '\n';
}
