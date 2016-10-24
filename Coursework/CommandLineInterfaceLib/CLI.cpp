/** @file */

#include "CLI.h"

#include <string>

#include "UtilityLib/StringUtils.h"

using namespace Utility;

namespace CommandLineInterface
{
/**
 * @brief String that is shown when the CLI prompt is displayed.
 */
const std::string CLI::PROMPT = "> ";

/**
 * @brief Create a new command line on given streams.
 * @param in Input stream
 * @param out Output stream
 *
 * Implicitly adds the "exit" command to exit the application.
 */
CLI::CLI(std::istream &in, std::ostream &out)
    : CommandContainer()
    , m_in(in)
    , m_out(out)
    , m_exitCode(CLI_RUN)
{
  /* Add exit command */
  m_commands.push_back(std::make_shared<Command>(
      "exit",
      [this](std::istream &in, std::ostream &out, std::vector<std::string> &argv) {
        this->exit();
        return 0;
      },
      "Exit the application."));
}

CLI::~CLI()
{
}

/**
 * @brief Runs the command line interface.
 * @return Exit code
 *
 * This should be called in main() after required setup logic.
 */
int CLI::run()
{
  while (m_exitCode == CLI_RUN)
  {
    m_out << PROMPT;

    std::string command;
    std::getline(m_in, command);

    std::vector<std::string> tokens;
    StringUtils::Split(tokens, command, ' ');

    handle(m_in, m_out, tokens);
  }

  return (int)m_exitCode;
}

/**
 * @brief Sets the flag to exit the application cleanly.
 */
void CLI::exit()
{
  m_exitCode = CLI_EXIT_CLEAN;
}
}
