/** @file */

#pragma once

#include <vector>

#include "Command.h"

namespace CommandLineInterface
{
class CommandContainer
{
public:
  CommandContainer();
  virtual ~CommandContainer();

  void registerCommand(Command *command);

  int handle(std::istream &in, std::ostream &out,
             std::vector<std::string> &tokens);
  void help(std::ostream &out);

protected:
  std::vector<Command *> m_commands;
};
}
