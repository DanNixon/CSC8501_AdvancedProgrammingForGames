/** @file */

#include <iostream>
#include <ctime>

#include "Coursework2Lib/CW2CommandLine.h"

int main()
{
  std::srand(std::time(0));
  Coursework2::CW2CommandLine cli(std::cin, std::cout);
  cli.initCLI();
  return cli.run();
}
