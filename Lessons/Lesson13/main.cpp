#include <iostream>
#include <string>

class CA
{
public:
  std::string val;
};

class CB
{
public:
  size_t val;
};

int main(void)
{
  auto v1 = new CA();
  v1->val = "Hello, World!";
  std::cout << v1->val << '\n';

  //v1 = new CB();

  return 0;
}
