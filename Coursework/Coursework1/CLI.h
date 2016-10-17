#pragma once

#include "CLICommand.h"
#include "CommandContainer.h"

enum CLIExit
{
  CLI_RUN = -1,
  CLI_EXIT_CLEAN = 0,
  CLI_EXIT_EXCEPTION = 1
};

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
