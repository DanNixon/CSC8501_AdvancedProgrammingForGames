/** @file */

#include <iostream>

#include "Coursework2Lib/CW2CommandLine.h"

int main()
{
  Coursework2::CW2CommandLine cli(std::cin, std::cout);
  cli.initCLI();
  return cli.run();
}
