#pragma once

#include <vector>

#include "CLICommand.h"

class CommandContainer
{
public:
  CommandContainer();
  virtual ~CommandContainer();

  void registerCommand(CLICommand *command);

  int handle(std::istream &in, std::ostream &out,
             std::vector<std::string> &tokens);
  void help(std::ostream &out);

protected:
  std::vector<CLICommand *> m_commands;
};
