#include <algorithm>
#include <iostream>
#include <locale>
#include <string>

void sample()
{
  static int8_t s8 = 0;
  static uint8_t u8 = 0;
  std::cout << "s8: " << (int)(s8++) << '\n';
  std::cout << "u8: " << (int)(u8++) << '\n';
}

int main()
{
  int retVal = 0;

  std::cout << "Hello, world!" << '\n';

  std::string name;

  std::cout << "Name:";
  std::getline(std::cin, name);

  std::cout << sizeof(std::string) << '\n';
  std::cout << sizeof(name) << '\n';

  std::cout << "Hello " << name << "!\n";

  auto firstInitialIt = std::find_if(
      name.begin(), name.end(), [](char c) -> bool { return isupper(c) > 0; });
  if (firstInitialIt != name.end())
  {
    size_t firstInitialIdx = firstInitialIt - name.begin();
    std::cout << name[firstInitialIdx];

    auto secondInitialIt =
        std::find_if(name.begin() + firstInitialIdx + 1, name.end(),
                     [](char c) -> bool { return isupper(c) > 0; });
    if (secondInitialIt != name.end())
    {
      size_t secondInitialIdx = secondInitialIt - name.begin();
      std::cout << name[secondInitialIdx];
    }
  }
  else
  {
    std::cout << "No initials found";
    retVal = 1;
  }
  std::cout << '\n';

  for (int i = 0; i < 300; i++)
  {
    std::cout << i << '\n';
    sample();
  }
  std::cout << '\n';

  std::cout << sizeof(int) << '\n';
  std::cout << sizeof(float) << '\n';
  std::cout << sizeof(char) << '\n';
  std::cout << sizeof(bool) << '\n';

  int i;
  float j;
  char k;
  bool l;

  std::cout << "i:";
  std::cin >> i;
  std::cout << "j:";
  std::cin >> j;
  std::cout << "k:";
  std::cin >> k;
  std::cout << "l:";
  std::cin >> l;

  std::cout << "i=" << i << '\n';
  std::cout << "j=" << j << '\n';
  std::cout << "k=" << k << '\n';
  std::cout << "l=" << l << '\n';

  std::cout << '\n';

  float a, b;

  std::cout << "a=";
  std::cin >> a;
  std::cout << "b=";
  std::cin >> b;

  std::cout << "a + b=" << (a + b) << '\n' << "a * b=" << (a * b) << '\n';

  std::cout << '\n';

  return retVal;
}
