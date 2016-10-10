#include <iostream>

float calc_avg(const int *arr, const int val);

int main(void)
{
  const int CONST_VALUE = 3;
  float ave;

  // stack based 1-d arrays
  int array_nums[CONST_VALUE] = {2, 4, 5};

  // print out the first element
  std::cout << "value at index 0 is " << array_nums[0] << "\n";

  // stack based 2-d arrays
  char naughts_n_xs[3][3];

  // set the middle square to x
  naughts_n_xs[1][1] = 'X';

  // arrays on the heap 1-d
  int *sum = new int[CONST_VALUE];

  for (int i = 0; i < CONST_VALUE; ++i)
  {
    std::cout << "enter a value...\n";
    std::cin >> sum[i];
  }

  ave = calc_avg(sum, CONST_VALUE);

  std::cout << "the average is " << ave << "\n";

  delete[] sum;

  return 0;
}

float calc_avg(const int *arr, const int val)
{
  int sum = 0;

  for (int i = 0; i < val; ++i)
    sum += arr[i];

  return (sum / (float)val);
}