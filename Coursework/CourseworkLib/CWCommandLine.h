/** @file */

#pragma once

#include "CommandLineInterfaceLib/CLI.h"

#include <string>

#include "CircuitSimulatorLib/Encoder.h"
#include "CommandLineInterfaceLib/SubCommand.h"

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
  static const std::string CLEAN_ENCODED_FILE_PATTERN;
  static const std::string NOISY_ENCODED_FILE_PATTERN;
  static const std::string WIRING_FILE_PATTERN;
  static const std::string TRELLIS_FILE_PATTERN;
  static const std::string CLEAN_DECODED_FILE_PATTERN;
  static const std::string NOISY_DECODED_FILE_PATTERN;

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
