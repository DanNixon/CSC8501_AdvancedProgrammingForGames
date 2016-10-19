/** @file */

#pragma once

#include "Command.h"
#include "CommandContainer.h"

namespace CommandLineInterface
{
/**
 * @brief Represents reasons for termination and their associated exit codes.
 */
enum CLIExit
{
  CLI_RUN = -1,
  CLI_EXIT_CLEAN = 0,
  CLI_EXIT_EXCEPTION = 1
};

/**
 * @class CLI
 * @author Dan Nixon
 * @brief Class handling execution of a persistent command line interface.
 */
class CLI : public CommandContainer
{
public:
  CLI(std::istream &in, std::ostream &out);
  virtual ~CLI();

  int run();

  void exit();

private:
  std::istream &m_in;
  std::ostream &m_out;

  std::string m_prompt;

  CLIExit m_exitCode;
};
}
