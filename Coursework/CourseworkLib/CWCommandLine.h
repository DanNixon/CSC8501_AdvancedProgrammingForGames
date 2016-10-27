/** @file */

#pragma once

#include "CommandLineInterfaceLib/CLI.h"

#include <map>
#include <string>

#include "CommandLineInterfaceLib/SubCommand.h"
#include "CircuitSimulatorLib/Encoder.h"

#include "PermutationGenerator.h"

namespace Coursework
{
/**
 * @class CWCommandLine
 * @author Dan Nixon
 * @brief CLI that provicdes an interface to courework functionality.
 */
class CWCommandLine : public CommandLineInterface::CLI
{
public:
  CWCommandLine(std::istream &in, std::ostream &out);
  virtual ~CWCommandLine();

  void initCLI();

private:
  CommandLineInterface::SubCommand_ptr generateComponentCmd();
  CommandLineInterface::SubCommand_ptr generateWireCmd();
  CommandLineInterface::SubCommand_ptr generatePermutationCmd();
  CommandLineInterface::SubCommand_ptr generatePresetCmd();
  void loadPreset(const std::string &preset);

private:
  CircuitSimulator::Encoder_ptr m_activeEncoder; //!< Current encoder
  PermutationGenerator *m_permutationGenerator;  //!< Current permutation generator
};
}
