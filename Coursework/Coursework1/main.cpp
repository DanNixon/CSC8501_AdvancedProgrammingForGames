/** @file */

#include <iostream>

#include "CW1CommandLine.h"

int main()
{
  CW1CommandLine cli(std::cin, std::cout);
  cli.generatePresets();
  cli.initCLI();
  return cli.run();
}
