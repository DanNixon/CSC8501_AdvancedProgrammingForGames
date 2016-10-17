#include <iostream>
#include <string>
#include <vector>

#include "Encoder.h"
#include "XORGate.h"

#include "CLI.h"
#include "CLICommand.h"
#include "CLISubCommand.h"

int main()
{
#if 0
  Encoder e;
  e.addComponent(new XORGate("xor1"));
  e.addComponent(new XORGate("xor2"));

  e.patch("input_bus.input_bit", "xor1.a");
  e.patch("input_bus.input_bit", "xor2.a");
  // e.patch("xor2.z", "xor1.b");
  e.patch("xor1.z", "output_bus.output_bit_1");
  e.patch("input_bus.input_bit", "output_bus.output_bit_2");

  std::cout << e << "\n\n";

  std::cout << "Output bit 1 = " << e.getOutput("output_bit_1") << '\n';
  std::cout << "Output bit 2 = " << e.getOutput("output_bit_2") << '\n';

  std::cout << '\n';

  e.setInput("input_bit", true);

  std::cout << "Output bit 1 = " << e.getOutput("output_bit_1") << '\n';
  std::cout << "Output bit 2 = " << e.getOutput("output_bit_2") << '\n';
#endif

  CommandLineInterface::CLI cli(std::cin, std::cout);

  cli.registerCommand(new CommandLineInterface::CLICommand(
      "test",
      [](std::istream &in, std::ostream &out, std::vector<std::string> argv) {
        out << "Test command.\n";
        return 0;
      },
      "Is a test."));

  CommandLineInterface::CLISubCommand *sub1 =
      new CommandLineInterface::CLISubCommand("sub1", "Test subcommand.");

  sub1->registerCommand(new CommandLineInterface::CLICommand(
      "list",
      [](std::istream &in, std::ostream &out, std::vector<std::string> argv) {
        out << "Test command => list.\n";
        return 0;
      },
      "Is a test 2."));

  cli.registerCommand(sub1);

  return cli.run();
}
