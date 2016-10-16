#pragma once

#include <vector>

#include "CLICommand.h"

enum CLIExit
{
  CLI_RUN = -1,
  CLI_EXIT_CLEAN = 0,
  CLI_EXIT_EXCEPTION = 1
};

class CLI
{
public:
  CLI(std::istream &in, std::ostream &out);
  virtual ~CLI();

  void registerCommand(CLICommand *command);
  int run();

  void exit();
  void help();

private:
  std::istream &m_in;
  std::ostream &m_out;

  std::string m_prompt;

  std::vector<CLICommand *> m_commands;

  CLIExit m_exitCode;
};
