/** @file */

#include <iostream>

#include "Coursework1Lib/CW1CommandLine.h"

int main()
{
  Coursework1::CW1CommandLine cli(std::cin, std::cout);
  cli.initCLI();
  return cli.run();
}
