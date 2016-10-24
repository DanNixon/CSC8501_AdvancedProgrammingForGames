/** @file */

#include <algorithm>
#include <iostream>
#include <string>

#include "CommandLineInterfaceLib/CLI.h"
#include "CommandLineInterfaceLib/Command.h"
#include "CommandLineInterfaceLib/SubCommand.h"

#include "CircuitSimulatorLib/ComponentFactory.h"
#include "CircuitSimulatorLib/Component_fwd.h"
#include "CircuitSimulatorLib/Encoder.h"

#include "UtilityLib/BinaryFileIO.h"

using namespace CommandLineInterface;
using namespace CircuitSimulator;
using namespace Utility;

int main()
{
  Encoder_ptr encoder = std::make_shared<Encoder>();

  SubCommand_ptr encoderComponentsCmd(new SubCommand("components", "Manage encoder components."));

  encoderComponentsCmd->registerCommand(Command_ptr(new Command(
      "list",
      [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) -> int {
        if (argv.size() > 1)
        {
          auto cIt = std::find_if(encoder->componentsBegin(), encoder->componentsEnd(),
                                  [&argv](Component_ptr c) { return c->id() == argv[1]; });
          if (cIt == encoder->componentsEnd())
            return 1;

          for (auto pIt = (*cIt)->pinsBegin(); pIt != (*cIt)->pinsEnd(); ++pIt)
            out << ((*pIt)->isInput() ? 'I' : ' ') << ((*pIt)->isOutput() ? 'O' : ' ') << ": "
                << (*pIt)->id() << '\n';
        }
        else
        {
          for (auto it = encoder->componentsBegin(); it != encoder->componentsEnd(); ++it)
            out << (*it)->name() << " : " << (*it)->id() << '\n';
        }
        return COMMAND_EXIT_CLEAN;
      },
      1, "Lists encoder components and component pins.")));

  encoderComponentsCmd->registerCommand(Command_ptr(
      new Command("add",
                  [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
                    std::vector<std::string> args(argv.begin() + 3, argv.end());
                    Component_ptr c = ComponentFactory::Create(argv[1], argv[2], args);
                    encoder->addComponent(c);
                    return COMMAND_EXIT_CLEAN;
                  },
                  3, "Adds a component to the encoder.")));

  encoderComponentsCmd->registerCommand(Command_ptr(new Command(
      "remove", [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv)
                    -> int { return encoder->removeComponent(argv[1]) ? COMMAND_EXIT_CLEAN : 1; },
      2, "Removes a component from the encoder.")));

  SubCommand_ptr encoderWireCmd(new SubCommand("wire", "Manage encoder wiring."));

  encoderWireCmd->registerCommand(Command_ptr(new Command(
      "list",
      [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        for (auto cIt = encoder->componentsBegin(); cIt != encoder->componentsEnd(); ++cIt)
          for (auto pIt = (*cIt)->pinsBegin(); pIt != (*cIt)->pinsEnd(); ++pIt)
            for (auto wIt = (*pIt)->outboundConnectionsBegin();
                 wIt != (*pIt)->outboundConnectionsEnd(); ++wIt)
              out << (*cIt)->id() << '.' << (*pIt)->id() << " -> " << (*wIt)->id() << '.'
                  << (*wIt)->parentComponent()->id() << '\n';
        return COMMAND_EXIT_CLEAN;
      },
      1, "Lists encoder wiring.")));

  encoderWireCmd->registerCommand(Command_ptr(
      new Command("add",
                  [encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
                    encoder->attachWire(argv[1], argv[2]);
                    return COMMAND_EXIT_CLEAN;
                  },
                  3, "Adds a wire between two pins.")));

  encoderWireCmd->registerCommand(Command_ptr(
      new Command("remove",
                  [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
                    encoder->removeWire(argv[1], argv[2]);
                    return COMMAND_EXIT_CLEAN;
                  },
                  1, "Removes a wire between two pins.")));

  SubCommand_ptr encoderPermutationCmd(
      new SubCommand("permutation", "Work with encoder permutations."));

  encoderPermutationCmd->registerCommand(Command_ptr(
      new Command("set_base",
                  [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
                    out << "TODO\n";
                    return COMMAND_EXIT_CLEAN;
                  },
                  1, "Sets the current encoder configuration as the base configuration.")));

  encoderPermutationCmd->registerCommand(Command_ptr(
      new Command("list",
                  [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
                    out << "TODO\n";
                    return COMMAND_EXIT_CLEAN;
                  },
                  1, "Lists all permutations.")));

  encoderPermutationCmd->registerCommand(Command_ptr(
      new Command("save",
                  [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
                    out << "TODO\n";
                    return COMMAND_EXIT_CLEAN;
                  },
                  1, "Saves all permutations to a text file.")));

  encoderPermutationCmd->registerCommand(Command_ptr(
      new Command("load",
                  [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
                    out << "TODO\n";
                    return COMMAND_EXIT_CLEAN;
                  },
                  1, "Loads a permutation into the active encoder.")));

  SubCommand_ptr encoderCmd(new SubCommand("encoder", "Configures encoder."));

  encoderCmd->registerCommand(encoderComponentsCmd);
  encoderCmd->registerCommand(encoderWireCmd);
  encoderCmd->registerCommand(encoderPermutationCmd);

  encoderCmd->registerCommand(Command_ptr(
      new Command("reset",
                  [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
                    encoder = std::make_shared<Encoder>();
                    return COMMAND_EXIT_CLEAN;
                  },
                  1, "Resets the state of the encoder.")));

  SubCommand_ptr encodeCmd(new SubCommand("encode", "Performs encoding."));

  encodeCmd->registerCommand(Command_ptr(
      new Command("string",
                  [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
                    std::vector<bool> dataIn;
                    std::vector<bool> dataOut;

                    BinaryFileIO::Read(dataIn, in);
                    dataOut.reserve(dataIn.size() * 2);

                    encoder->encode(dataIn, dataOut);

                    for (auto it = dataOut.begin(); it != dataOut.end(); ++it)
                      out << (*it);
                    out << "\n";

                    return COMMAND_EXIT_CLEAN;
                  },
                  1, "Encodes a string.")));

  encodeCmd->registerCommand(Command_ptr(
      new Command("file",
                  [&encoder](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
                    std::vector<bool> dataIn;
                    std::vector<bool> dataOut;

                    BinaryFileIO::ReadFile(dataIn, argv[1]);
                    dataOut.reserve(dataIn.size() * 2);

                    encoder->encode(dataIn, dataOut);

                    BinaryFileIO::WriteFile(dataOut, argv[2]);

                    return COMMAND_EXIT_CLEAN;
                  },
                  3, "Encodes data from a file.")));

  CLI cli(std::cin, std::cout);

  cli.registerCommand(encoderCmd);
  cli.registerCommand(encodeCmd);

  return cli.run();
}
