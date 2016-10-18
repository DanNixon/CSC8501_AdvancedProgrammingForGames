#include <iostream>
#include <string>
#include <vector>

#include "CommandLineInterfaceLib/CLI.h"
#include "CommandLineInterfaceLib/Command.h"
#include "CommandLineInterfaceLib/SubCommand.h"

int main()
{
  CommandLineInterface::CLI cli(std::cin, std::cout);

  cli.registerCommand(new CommandLineInterface::Command(
      "test",
      [](std::istream &in, std::ostream &out, std::vector<std::string> argv) {
        out << "Test command.\n";
        return 0;
      },
      "Is a test."));

  CommandLineInterface::SubCommand *sub1 =
      new CommandLineInterface::SubCommand("sub1", "Test subcommand.");

  sub1->registerCommand(new CommandLineInterface::Command(
      "list",
      [](std::istream &in, std::ostream &out, std::vector<std::string> argv) {
        out << "Test command => list.\n";
        return 0;
      },
      "Is a test 2."));

  cli.registerCommand(sub1);

  return cli.run();
}
