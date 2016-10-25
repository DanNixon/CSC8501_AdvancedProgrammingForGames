/** @file */

#include <iostream>
#include <ctime>

#include "Coursework1Lib/CW1CommandLine.h"

int main()
{
  std::srand(std::time(0));
  Coursework1::CW1CommandLine cli(std::cin, std::cout);
  cli.initCLI();
  return cli.run();
}
