/** @file */

#pragma once

#include "CommandLineInterfaceLib/CLI.h"
#include "CommandLineInterfaceLib/Command.h"
#include "CommandLineInterfaceLib/SubCommand.h"

#include "CircuitSimulatorLib/Encoder.h"

class CW1CommandLine : public CommandLineInterface::CLI
{
public:
  CW1CommandLine(std::istream &in, std::ostream &out);
  virtual ~CW1CommandLine();

  void init();

private:
  CommandLineInterface::SubCommand_ptr generateComponentCmd();
  CommandLineInterface::SubCommand_ptr generateWireCmd();
  CommandLineInterface::SubCommand_ptr generatePermutationCmd();
  CommandLineInterface::SubCommand_ptr generatePresetCmd();

private:
  CircuitSimulator::Encoder_ptr m_activeEncoder;
};

