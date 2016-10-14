#include <iostream>
#include <string>

#include "Encoder.h"

int main()
{
  Encoder e("e1");

  for (auto it = e.inputs(); it != e.inputsEnd(); ++it)
    std::cout << it->first << " = " << it->second << '\n';

  for (auto it = e.outputs(); it != e.outputsEnd(); ++it)
    std::cout << it->first << " = " << it->second << '\n';

  std::string s;
  std::getline(std::cin, s);

  return 0;
}
