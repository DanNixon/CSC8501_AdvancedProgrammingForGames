/** @file */

#include <iostream>
#include <string>

#include "CommandLineInterfaceLib/CLI.h"
#include "CommandLineInterfaceLib/Command.h"
#include "CommandLineInterfaceLib/SubCommand.h"

using namespace CommandLineInterface;

int main()
{
  SubCommand_ptr encoderComponents(
      new SubCommand("components", "Manage encoder components."));

  encoderComponents->registerCommand(Command_ptr(new Command(
      "list",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Lists encoder components.")));

  encoderComponents->registerCommand(Command_ptr(new Command(
      "add",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Adds a component to the encoder.")));

  encoderComponents->registerCommand(Command_ptr(new Command(
      "remove",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Removes a component from the encoder.")));

  SubCommand_ptr encoderWire(new SubCommand("wire", "Manage encoder wiring."));

  encoderWire->registerCommand(Command_ptr(new Command(
      "reset",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Resets encoder wiring.")));

  encoderWire->registerCommand(Command_ptr(new Command(
      "list",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Lists encoder wiring.")));

  encoderWire->registerCommand(Command_ptr(new Command(
      "add",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Adds a wire between two pins.")));

  encoderWire->registerCommand(Command_ptr(new Command(
      "remove",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Removes a wire between two pins.")));

  SubCommand_ptr encoderPermutation(
      new SubCommand("permutation", "Work with encoder permutations."));

  encoderPermutation->registerCommand(Command_ptr(new Command(
      "set_base",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
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
      "load",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Loads a permutation into the active configuration.")));

  SubCommand_ptr encoder(new SubCommand("encoder", "Configures encoder."));

  encoder->registerCommand(encoderComponents);
  encoder->registerCommand(encoderWire);
  encoder->registerCommand(encoderPermutation);

  encoder->registerCommand(Command_ptr(new Command(
      "reset",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Resets the state of the encoder.")));

  SubCommand_ptr encode(new SubCommand("encode", "Performs encoding."));

  encode->registerCommand(Command_ptr(new Command(
      "string",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Encodes a string.")));

  encode->registerCommand(Command_ptr(new Command(
      "file",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return 0;
      },
      "Encodes data from a file.")));

  CLI cli(std::cin, std::cout);
  cli.registerCommand(encoder);
  cli.registerCommand(encode);

  return cli.run();
}
