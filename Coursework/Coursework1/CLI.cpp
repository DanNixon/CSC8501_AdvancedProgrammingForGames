#include "CLI.h"

#include <algorithm>
#include <string>

#include "StringUtils.h"

CLI::CLI(std::istream &in, std::ostream &out)
    : m_in(in)
    , m_out(out)
    , m_prompt("> ")
    , m_exitCode(CLI_RUN)
{
  // Add exit command
  m_commands.push_back(new CLICommand("exit",
                                      [this](std::vector<std::string> argv) {
                                        this->exit();
                                        return 0;
                                      },
                                      "Exit the application."));

  // Add help command
  m_commands.push_back(new CLICommand("help",
                                      [this](std::vector<std::string> argv) {
                                        this->help();
                                        return 0;
                                      },
                                      "Shows command usage."));
}

CLI::~CLI()
{
  for (auto it = m_commands.begin(); it != m_commands.end(); ++it)
    delete *it;
  m_commands.clear();
}

void CLI::registerCommand(CLICommand *command)
{
  m_commands.push_back(command);
}

int CLI::run()
{
  while (m_exitCode == CLI_RUN)
  {
    m_out << m_prompt;

    std::string command;
    std::getline(m_in, command);

    std::vector<std::string> tokens;
    StringUtils::Split(tokens, command, ' ');

    auto it = std::find_if(
        m_commands.begin(), m_commands.end(),
        [tokens](CLICommand *c) { return c->commandName() == tokens[0]; });
    if (it == m_commands.end())
    {
      m_out << "Command \"" << tokens[0] << "\" not found.\n";
      continue;
    }

    (*it)->handle(tokens);
  }

  return (int)m_exitCode;
}

void CLI::exit()
{
  m_exitCode = CLI_EXIT_CLEAN;
}

void CLI::help()
{
  m_out << "Command usage:\n";

  for (auto it = m_commands.begin(); it != m_commands.end(); ++it)
    m_out << ' ' << (*it)->commandName() << "\t\t: " << (*it)->description()
          << '\n';
}