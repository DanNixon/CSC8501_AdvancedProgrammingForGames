/** @file */

#include <iostream>
#include <string>

#include "CommandLineInterfaceLib/CLI.h"
#include "CommandLineInterfaceLib/Command.h"
#include "CommandLineInterfaceLib/SubCommand.h"

#include "CircuitSimulatorLib/Encoder.h"

using namespace CommandLineInterface;
using namespace CircuitSimulator;

int main()
{
  Encoder_ptr encoder = std::make_shared<Encoder>();

  SubCommand_ptr encoderComponents(
      new SubCommand("components", "Manage encoder components."));

  encoderComponents->registerCommand(Command_ptr(new Command(
      "list",
      [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Lists encoder components.")));

  encoderComponents->registerCommand(Command_ptr(new Command(
      "add",
      [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Adds a component to the encoder.")));

  encoderComponents->registerCommand(Command_ptr(new Command(
      "remove",
      [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Removes a component from the encoder.")));

  SubCommand_ptr encoderWire(new SubCommand("wire", "Manage encoder wiring."));

  encoderWire->registerCommand(Command_ptr(new Command(
      "reset",
      [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Resets encoder wiring.")));

  encoderWire->registerCommand(Command_ptr(new Command(
      "list",
      [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Lists encoder wiring.")));

  encoderWire->registerCommand(Command_ptr(new Command(
      "add",
      [encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Adds a wire between two pins.")));

  encoderWire->registerCommand(Command_ptr(new Command(
      "remove",
      [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Removes a wire between two pins.")));

  SubCommand_ptr encoderPermutation(
      new SubCommand("permutation", "Work with encoder permutations."));

  encoderPermutation->registerCommand(Command_ptr(new Command(
      "set_base",
      [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Sets the current encoder configuration as the base configuration.")));

  encoderPermutation->registerCommand(Command_ptr(new Command(
      "list",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Lists all permutations.")));

  encoderPermutation->registerCommand(Command_ptr(new Command(
      "save",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Saves all permutations to a text file.")));

  encoderPermutation->registerCommand(Command_ptr(new Command(
      "load",
      [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Loads a permutation into the active encoder.")));

  SubCommand_ptr encoderCmd(new SubCommand("encoder", "Configures encoder."));

  encoderCmd->registerCommand(encoderComponents);
  encoderCmd->registerCommand(encoderWire);
  encoderCmd->registerCommand(encoderPermutation);

  encoderCmd->registerCommand(Command_ptr(new Command(
      "reset",
      [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        encoder = std::make_shared<Encoder>();
        return 0;
      },
      "Resets the state of the encoder.")));

  SubCommand_ptr encodeCmd(new SubCommand("encode", "Performs encoding."));

  encodeCmd->registerCommand(Command_ptr(new Command(
      "string",
      [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Encodes a string.")));

  encodeCmd->registerCommand(Command_ptr(new Command(
      "file",
      [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Encodes data from a file.")));

  CLI cli(std::cin, std::cout);
  cli.registerCommand(encoderCmd);
  cli.registerCommand(encodeCmd);

  return cli.run();
}
