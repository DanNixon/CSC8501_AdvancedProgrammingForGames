/** @file */

#include <ctime>
#include <iostream>

#include "Coursework2Lib/CW2CommandLine.h"

/**
 * @brief Entry point.
 * @return Exit code
 */
int main()
{
  std::srand((unsigned int)std::time(0));
  Coursework2::CW2CommandLine cli(std::cin, std::cout);
  cli.initCLI();
  return cli.run();
}
