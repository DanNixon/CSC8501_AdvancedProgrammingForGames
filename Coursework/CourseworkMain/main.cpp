/** @file */

#include <ctime>
#include <iostream>

#include "CourseworkLib/CWCommandLine.h"

/**
 * @brief Entry point.
 * @return Exit code
 */
int main()
{
  /* Seed random number generator. */
  std::srand((unsigned int)std::time(0));

  /* Init and run CLI. */
  Coursework::CWCommandLine cli(std::cin, std::cout);
  cli.initCLI();
  return cli.run();
}
