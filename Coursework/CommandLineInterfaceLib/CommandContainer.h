/** @file */

#pragma once

#include <vector>

#include "Command.h"

namespace CommandLineInterface
{
/**
 * @class CommandContainer
 * @author Dan Nixon
 * @brief Abstract class providing functionality required to contain and select
 *        Command.
 */
class CommandContainer
{
public:
  CommandContainer();
  virtual ~CommandContainer();

  void registerCommand(Command_ptr command);

  int handle(std::istream &in, std::ostream &out, std::vector<std::string> &tokens);
  void help(std::ostream &out);

protected:
  std::vector<Command_ptr> m_commands; //!< Commands in this container
};
}
