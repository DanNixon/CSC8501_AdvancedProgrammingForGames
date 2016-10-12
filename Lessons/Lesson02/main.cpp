#include <functional>
#include <iostream>

void productStr(std::ostream &str, double a, double b);

auto add = [](double x, double y) -> double { return x + y; };
auto minus = [](double x, double y) -> double { return x - y; };
auto product = [](double x, double y) -> double { return x * y; };
auto quotient = [](double x, double y) -> double { return x / y; };

int main()
{
  double a, b, c;
  char op;

  while (true)
  {
    std::cout << "Expression: ";
    std::cin >> a >> op >> b;

    if (std::cin.fail())
      return 1;

    switch (op)
    {
    case '+':
      c = add(a, b);
      break;

    case '-':
      c = minus(a, b);
      break;

    case '*':
      c = product(a, b);
      break;

    case '/':
      c = quotient(a, b);
      break;

    default:
      return 2;
    }

    std::cout << a << ' ' << op << ' ' << b << " = " << c << '\n';
  }

  return 0;
}

void productStr(std::ostream &str, double a, double b)
{
  str << a << '*' << b << '=' << (a * b) << '\n';
}
