#include <iostream>
#include <vector>

bool geqZero(int x);
int getNegativeInt(bool &result, size_t limit = std::numeric_limits<size_t>::max());
int add(int x, int y);
int loopedFactorial(int x);
int recursiveFactorial(int x);
int recursiveFactorialInv(int x, int total = 1);

int main()
{
  bool gotNegative;
  int n = getNegativeInt(gotNegative, 5);
  std::cout << "Got a negative: " << gotNegative << '\n';
  if (gotNegative)
    std::cout << "n = " << n << '\n\n';

  std::vector<int> a = {-1, 0, 1};
  for (auto it = a.begin(); it != a.end(); ++it)
    std::cout << *it << " >= 0  ->  " << geqZero(*it) << '\n';

  std::vector<int> b = {0, 1, 2, 3, 4, 5, 6, 7, 100};
  for (auto it = b.begin(); it != b.end(); ++it)
  {
    int lf = loopedFactorial(*it);
    int rf = recursiveFactorial(*it);
    int rfi = recursiveFactorialInv(*it);

    std::cout << *it << "\tLooped: " << lf << "\tRecursive: " << rf << "\tRecursive (inv): " << rfi
              << '\n';

    if (lf != rf || lf != rfi)
      std::cout << "Well, fuck. (" << *it << ")\n";
  }

  int total = 0;
  int x;

  std::cout << "Please enter numbers, will finish if sum of factorals exceeds 2000\n";

  while (total <= 2000)
  {
    std::cin >> x;
    total = add(loopedFactorial(x), total);
  }

  std::cout << "The total is " << total << '\n';

  if (total > 3000)
  {
    std::cout << "you overshot by a lot!\n";
  }
  else
  {
    std::cout << "You just went over\n"
              << "Only over by " << total - 2000 << '\n';
  }

  return 0;
}

bool geqZero(int x)
{
  return x >= 0;
}

int getNegativeInt(bool &result, size_t limit)
{
  int n = 0;
  result = false;

  std::cout << "Enter some numbers.\n";

  for (size_t i = 0; i < limit; i++)
  {
    std::cout << "n = ";
    std::cin >> n;

    if (!geqZero(n))
    {
      result = true;
      break;
    }
  }

  return n;
}

int add(int x, int y)
{
  return x + y;
}

int loopedFactorial(int x)
{
  int facSum = 1;

  for (int count = x; count > 0; count--)
    facSum = facSum * count;

  return facSum;
}

int recursiveFactorial(int x)
{
  if (x == 0)
    return 1;

  return x * recursiveFactorial(x - 1);
}

int recursiveFactorialInv(int x, int total)
{
  if (x == 0)
    return total;

  total *= x;
  return recursiveFactorialInv(x - 1, total);
}
