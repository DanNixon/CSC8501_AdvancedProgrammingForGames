#pragma once

#include "CLICommand.h"
#include "CommandContainer.h"

class CLISubCommand : public CLICommand, public CommandContainer
{
public:
  CLISubCommand(const std::string &commandName, const std::string &desc = "")
      : CLICommand(commandName,
                   [this](std::istream &in, std::ostream &out,
                          std::vector<std::string> argv) {
                     argv.erase(argv.begin());
                     return this->handle(in, out, argv);
                   },
                   desc)
      , CommandContainer()
  {
  }

  virtual ~CLISubCommand()
  {
  }
};