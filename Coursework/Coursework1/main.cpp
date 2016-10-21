/** @file */

#include <iostream>
#include <string>

#include "CommandLineInterfaceLib/CLI.h"
#include "CommandLineInterfaceLib/Command.h"
#include "CommandLineInterfaceLib/SubCommand.h"

using namespace CommandLineInterface;

int main()
{
  SubCommand *encoderPermutation =
      new SubCommand("permutation", "Work with encoder permutations.");

  encoderPermutation->registerCommand(new Command(
      "list",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv)
      {
        out << "TODO\n";
        return 0;
      },
      "Lists all permutations."));

  encoderPermutation->registerCommand(new Command(
      "load",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv)
      {
        out << "TODO\n";
        return 0;
      },
      "Loads a permutation into the active configuration."));

  SubCommand *encoderWire = new SubCommand("wire", "Manage encoder wiring.");

  encoderWire->registerCommand(new Command(
      "reset",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv)
      {
        out << "TODO\n";
        return 0;
      },
      "Resets encoder wiring."));

  encoderWire->registerCommand(new Command(
      "list",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv)
      {
        out << "TODO\n";
        return 0;
      },
      "Lists encoder wiring."));

  encoderWire->registerCommand(new Command(
      "add",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv)
      {
        out << "TODO\n";
        return 0;
      },
      "Adds a wire between two pins."));

  encoderWire->registerCommand(new Command(
      "remove",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv)
      {
        out << "TODO\n";
        return 0;
      },
      "Removes a wire between two pins."));

  SubCommand *encoder = new SubCommand("encoder", "Configures encoder.");

  encoder->registerCommand(encoderWire);
  encoder->registerCommand(encoderPermutation);

  encoder->registerCommand(new Command(
      "reset",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv)
      {
        out << "TODO\n";
        return 0;
      },
      "Resets the state of the encoder."));

  SubCommand *encode = new SubCommand("encode", "Performs encoding.");

  encode->registerCommand(new Command(
      "string",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv)
      {
        out << "TODO\n";
        return 0;
      },
      "Encodes a string."));

  encode->registerCommand(new Command(
      "file",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv)
      {
        out << "TODO\n";
        return 0;
      },
      "Encodes data from a file."));

  CLI cli(std::cin, std::cout);
  cli.registerCommand(encoder);
  cli.registerCommand(encode);

  return cli.run();
}
