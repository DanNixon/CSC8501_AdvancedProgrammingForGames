/** @file */

#include <ctime>
#include <iostream>

#include "Coursework1Lib/CW1CommandLine.h"

int main()
{
  std::srand((unsigned int)std::time(0));
  Coursework1::CW1CommandLine cli(std::cin, std::cout);
  cli.initCLI();
  return cli.run();
}
