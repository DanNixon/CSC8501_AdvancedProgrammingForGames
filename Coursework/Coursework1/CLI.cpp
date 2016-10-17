#include "CLI.h"

#include <string>

#include "StringUtils.h"

CLI::CLI(std::istream &in, std::ostream &out)
    : CommandContainer()
    , m_in(in)
    , m_out(out)
    , m_prompt("> ")
    , m_exitCode(CLI_RUN)
{
  // Add exit command
  m_commands.push_back(
      new CLICommand("exit",
                     [this](std::istream &in, std::ostream &out,
                            std::vector<std::string> argv) {
                       this->exit();
                       return 0;
                     },
                     "Exit the application."));
}

CLI::~CLI()
{
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

    handle(m_in, m_out, tokens);
  }

  return (int)m_exitCode;
}

void CLI::exit()
{
  m_exitCode = CLI_EXIT_CLEAN;
}
