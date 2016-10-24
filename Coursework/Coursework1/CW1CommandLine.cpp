/** @file */

#include "CW1CommandLine.h"

#include <algorithm>

#include "CircuitSimulatorLib/ComponentFactory.h"
#include "UtilityLib/BinaryFileIO.h"

using namespace CommandLineInterface;
using namespace CircuitSimulator;
using namespace Utility;

CW1CommandLine::CW1CommandLine(std::istream &in, std::ostream &out)
    : CLI(in, out)
    , m_activeEncoder(std::make_shared<Encoder>())
{
}

CW1CommandLine::~CW1CommandLine()
{
}

void CW1CommandLine::init()
{
  SubCommand_ptr encoderCmd = std::make_shared<SubCommand>("encoder", "Configures encoder.");
  encoderCmd->registerCommand(generateComponentCmd());
  encoderCmd->registerCommand(generateWireCmd());
  encoderCmd->registerCommand(generatePermutationCmd());
  encoderCmd->registerCommand(generatePresetCmd());

  encoderCmd->registerCommand(std::make_shared<Command>(
      "reset",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        this->m_activeEncoder = std::make_shared<Encoder>();
        return COMMAND_EXIT_CLEAN;
      },
      1, "Resets the state of the encoder."));

  SubCommand_ptr encodeCmd = std::make_shared<SubCommand>("encode", "Performs encoding.");

  encodeCmd->registerCommand(std::make_shared<Command>(
      "string",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        std::vector<bool> dataIn;
        std::vector<bool> dataOut;

        BinaryFileIO::Read(dataIn, in);
        dataOut.reserve(dataIn.size() * 2);

        this->m_activeEncoder->encode(dataIn, dataOut);

        for (auto it = dataOut.begin(); it != dataOut.end(); ++it)
          out << (*it);
        out << "\n";

        return COMMAND_EXIT_CLEAN;
      },
      1, "Encodes a string."));

  encodeCmd->registerCommand(std::make_shared<Command>(
      "file",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        std::vector<bool> dataIn;
        std::vector<bool> dataOut;

        BinaryFileIO::ReadFile(dataIn, argv[1]);
        dataOut.reserve(dataIn.size() * 2);

        this->m_activeEncoder->encode(dataIn, dataOut);

        BinaryFileIO::WriteFile(dataOut, argv[2]);

        return COMMAND_EXIT_CLEAN;
      },
      3, "Encodes data from a file."));

  registerCommand(encoderCmd);
  registerCommand(encodeCmd);
}

SubCommand_ptr CW1CommandLine::generateComponentCmd()
{
  SubCommand_ptr cmd = std::make_shared<SubCommand>("components", "Manage encoder components.");

  cmd->registerCommand(std::make_shared<Command>(
      "list",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) -> int {
        if (argv.size() > 1)
        {
          auto cIt = std::find_if(this->m_activeEncoder->componentsBegin(),
                                  this->m_activeEncoder->componentsEnd(),
                                  [&argv](Component_ptr c) { return c->id() == argv[1]; });
          if (cIt == this->m_activeEncoder->componentsEnd())
            return 1;

          for (auto pIt = (*cIt)->pinsBegin(); pIt != (*cIt)->pinsEnd(); ++pIt)
            out << ((*pIt)->isInput() ? 'I' : ' ') << ((*pIt)->isOutput() ? 'O' : ' ') << ": "
                << (*pIt)->id() << '\n';
        }
        else
        {
          for (auto it = this->m_activeEncoder->componentsBegin();
               it != this->m_activeEncoder->componentsEnd(); ++it)
            out << (*it)->name() << " : " << (*it)->id() << '\n';
        }
        return COMMAND_EXIT_CLEAN;
      },
      1, "Lists encoder components and component pins."));

  cmd->registerCommand(std::make_shared<Command>(
      "add",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        std::vector<std::string> args(argv.begin() + 3, argv.end());
        Component_ptr c = ComponentFactory::Create(argv[1], argv[2], args);
        this->m_activeEncoder->addComponent(c);
        return COMMAND_EXIT_CLEAN;
      },
      3, "Adds a component to the encoder."));

  cmd->registerCommand(std::make_shared<Command>(
      "remove",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) -> int {
        return this->m_activeEncoder->removeComponent(argv[1]) ? COMMAND_EXIT_CLEAN : 1;
      },
      2, "Removes a component from the encoder."));

  return cmd;
}

SubCommand_ptr CW1CommandLine::generateWireCmd()
{
  SubCommand_ptr cmd = std::make_shared<SubCommand>("wire", "Manage encoder wiring.");

  cmd->registerCommand(std::make_shared<Command>(
      "list",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        for (auto cIt = this->m_activeEncoder->componentsBegin();
             cIt != this->m_activeEncoder->componentsEnd(); ++cIt)
          for (auto pIt = (*cIt)->pinsBegin(); pIt != (*cIt)->pinsEnd(); ++pIt)
            for (auto wIt = (*pIt)->outboundConnectionsBegin();
                 wIt != (*pIt)->outboundConnectionsEnd(); ++wIt)
              out << (*cIt)->id() << '.' << (*pIt)->id() << " -> " << (*wIt)->id() << '.'
                  << (*wIt)->parentComponent()->id() << '\n';
        return COMMAND_EXIT_CLEAN;
      },
      1, "Lists encoder wiring."));

  cmd->registerCommand(std::make_shared<Command>(
      "add",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        this->m_activeEncoder->attachWire(argv[1], argv[2]);
        return COMMAND_EXIT_CLEAN;
      },
      3, "Adds a wire between two pins."));

  cmd->registerCommand(std::make_shared<Command>(
      "remove",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        this->m_activeEncoder->removeWire(argv[1], argv[2]);
        return COMMAND_EXIT_CLEAN;
      },
      1, "Removes a wire between two pins."));

  return cmd;
}

SubCommand_ptr CW1CommandLine::generatePermutationCmd()
{
  SubCommand_ptr cmd =
      std::make_shared<SubCommand>("permutation", "Work with encoder permutations.");

  cmd->registerCommand(std::make_shared<Command>(
      "set_base",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return COMMAND_EXIT_CLEAN;
      },
      1, "Sets the current encoder configuration as the base configuration."));

  cmd->registerCommand(std::make_shared<Command>(
      "list",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return COMMAND_EXIT_CLEAN;
      },
      1, "Lists all permutations."));

  cmd->registerCommand(std::make_shared<Command>(
      "save",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return COMMAND_EXIT_CLEAN;
      },
      1, "Saves all permutations to a text file."));

  cmd->registerCommand(std::make_shared<Command>(
      "load",
      [](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return COMMAND_EXIT_CLEAN;
      },
      1, "Loads a permutation into the active encoder."));

  return cmd;
}

SubCommand_ptr CW1CommandLine::generatePresetCmd()
{
  SubCommand_ptr cmd = std::make_shared<SubCommand>("presets", "Work with encoder presets.");

  cmd->registerCommand(std::make_shared<Command>(
      "list",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return COMMAND_EXIT_CLEAN;
      },
      1, "Lists all encoder presets."));

  cmd->registerCommand(std::make_shared<Command>(
      "load",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        out << "TODO\n";
        return COMMAND_EXIT_CLEAN;
      },
      2, "Loads an encoder presets."));

  return cmd;
}
