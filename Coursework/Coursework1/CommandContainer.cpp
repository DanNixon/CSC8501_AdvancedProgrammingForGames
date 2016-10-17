#include "CommandContainer.h"

#include <algorithm>

CommandContainer::CommandContainer()
{
  // Add help command
  m_commands.push_back(
      new CLICommand("help",
                     [this](std::istream &in, std::ostream &out,
                            std::vector<std::string> argv) {
                       this->help(out);
                       return 0;
                     },
                     "Shows command usage."));
}

CommandContainer::~CommandContainer()
{
  for (auto it = m_commands.begin(); it != m_commands.end(); ++it)
    delete *it;
  m_commands.clear();
}

void CommandContainer::registerCommand(CLICommand *command)
{
  m_commands.push_back(command);
}

int CommandContainer::handle(std::istream &in, std::ostream &out,
                             std::vector<std::string> &tokens)
{
  if (tokens.size() == 0)
  {
    help(out);
    return -1;
  }

  auto it = std::find_if(
      m_commands.begin(), m_commands.end(),
      [tokens](CLICommand *c) { return c->commandName() == tokens[0]; });
  if (it == m_commands.end())
  {
    out << "Command \"" << tokens[0] << "\" not found.\n";
    return -1;
  }

  return (*it)->handleCmdFunc(in, out, tokens);
}

void CommandContainer::help(std::ostream &out)
{
  out << "Command usage:\n";

  for (auto it = m_commands.begin(); it != m_commands.end(); ++it)
    out << ' ' << (*it)->commandName() << "\t\t: " << (*it)->description()
        << '\n';
}
