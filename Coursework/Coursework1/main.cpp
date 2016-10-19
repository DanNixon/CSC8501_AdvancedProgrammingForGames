/** @file */

#include <iostream>
#include <string>

#include "CommandLineInterfaceLib/CLI.h"
#include "CommandLineInterfaceLib/Command.h"
#include "CommandLineInterfaceLib/SubCommand.h"

int main()
{
  CommandLineInterface::CLI cli(std::cin, std::cout);

  // TODO

  return cli.run();
}
