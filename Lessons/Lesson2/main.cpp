#include <iostream>

double add(double x, double y);
double minus(double x, double y);
double product(double a, double b);
void product(std::ostream &str, double a, double b);
double quotient(double a, double b);

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

    std::cout << a << op << b << '=' << c << '\n';
  }

  return 0;
}

double add(double x, double y)
{
  return x + y;
}

double minus(double x, double y)
{
  return x - y;
}

double product(double a, double b)
{
  return a * b;
}

void product(std::ostream &str, double a, double b)
{
  str << a << '*' << b << '=' << (a * b) << '\n';
}

double quotient(double a, double b)
{
  return a / b;
}
