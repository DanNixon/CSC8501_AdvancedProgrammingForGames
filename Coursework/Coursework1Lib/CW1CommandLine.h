/** @file */

#pragma once

#include "CommandLineInterfaceLib/CLI.h"

#include <map>
#include <string>

#include "CommandLineInterfaceLib/SubCommand.h"

#include "CircuitSimulatorLib/Encoder.h"

#include "Permutation.h"

namespace Coursework1
{
class CW1CommandLine : public CommandLineInterface::CLI
{
public:
  CW1CommandLine(std::istream &in, std::ostream &out);
  virtual ~CW1CommandLine();

  void initCLI();

private:
  CommandLineInterface::SubCommand_ptr generateComponentCmd();
  CommandLineInterface::SubCommand_ptr generateWireCmd();
  CommandLineInterface::SubCommand_ptr generatePermutationCmd();
  CommandLineInterface::SubCommand_ptr generatePresetCmd();

private:
  CircuitSimulator::Encoder_ptr m_activeEncoder;
  std::map<std::string, CircuitSimulator::Encoder_ptr> m_encoderPresets;
  std::vector<Permutation> m_permutations;
};
}