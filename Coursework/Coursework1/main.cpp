#include <iostream>
#include <string>
#include <vector>

#include "Encoder.h"
#include "SerialRegisterArray.h"
#include "XORGate.h"

#include "CLI.h"
#include "CLICommand.h"
#include "CLISubCommand.h"

int main()
{
#if 1
  CircuitSimulator::Encoder e;
  e.addComponent(new CircuitSimulator::XORGate("xor1"));
  e.addComponent(new CircuitSimulator::XORGate("xor2"));
  e.addComponent(new CircuitSimulator::SerialRegisterArray("r", 4));

  // Wiring as per example in CW spec
  e.wireUp("input_bus.bit_0", "r.bit_0");
  e.wireUp("input_bus.bit_0", "xor2.a");
  e.wireUp("r.bit_1", "xor2.b");
  e.wireUp("xor2.z", "output_bus.bit_1");
  e.wireUp("r.bit_2", "xor1.a");
  e.wireUp("r.bit_3", "xor1.b");
  e.wireUp("xor1.z", "output_bus.bit_0");

  std::cout << e << "\n\n";

  std::cout << "Output bit 0 = " << e.getOutput("bit_0") << '\n';
  std::cout << "Output bit 1 = " << e.getOutput("bit_1") << '\n';
  std::cout << '\n';

  std::vector<bool> inputBits = {true, false, false, true};

  for (auto it = inputBits.begin(); it != inputBits.end(); ++it)
  {
    e.setInput("bit_0", *it);
    e.advanceRegisters(-1);

    std::cout << "Input bit = " << e.getInput("bit_0") << '\n';
    std::cout << "Output bit 0 = " << e.getOutput("bit_0") << '\n';
    std::cout << "Output bit 1 = " << e.getOutput("bit_1") << '\n';
    std::cout << '\n';
  }
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
