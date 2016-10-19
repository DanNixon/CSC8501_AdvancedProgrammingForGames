/** @file */

#pragma once

#include "Command.h"
#include "CommandContainer.h"

namespace CommandLineInterface
{
/**
 * @class SubCommand
 * @author Dan Nixon
 * @brief Command that holds a collection of additional commands.
 */
class SubCommand : public Command, public CommandContainer
{
public:
  SubCommand(const std::string &commandName, const std::string &desc = "")
      : Command(commandName,
                [this](std::istream &in, std::ostream & out,
                       std::vector<std::string> argv)
                {
                  argv.erase(argv.begin());
                  return this->handle(in, out, argv);
                },
                desc)
      , CommandContainer()
  {
  }

  virtual ~SubCommand()
  {
  }
};
}
