/** @file */

#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace CommandLineInterface
{
/**
 * @class Command
 * @author Dan Nixon
 * @brief Stores data for a single executable CLI command.
 */
class Command
{
public:
  /**
   * @brief Function type for command handler functions.
   *
   * Takes a reference to the input and output streams and a vector of string
   * parameters as parameters and returns an exit code.
   */
  typedef std::function<int(std::istream &in, std::ostream &out, std::vector<std::string> &argv)>
      CMDHandlerFunc;

public:
  /**
   * @brief Creates a new command.
   * @param commandName Name of the command
   * @param func Function to be executed when command is invoked
   * @param desc Short description of the command
   *
   * commandName is what is matched to input on the command line when selecting
   * the command to be executed.
   *
   * desc is shown when the CommandContainer::help() function is invoked.
   */
  Command(const std::string &commandName, CMDHandlerFunc func, const std::string &desc = "")
      : m_commandName(commandName)
      , m_handlerFunc(func)
      , m_description(desc)
  {
  }

  virtual ~Command()
  {
  }

  /**
   * @brief Gets the name of the command.
   * @return Command name
   */
  inline std::string commandName() const
  {
    return m_commandName;
  }

  /**
   * @brief Gets a description of the command.
   * @return Command description
   */
  inline std::string description() const
  {
    return m_description;
  }

  /**
   * @brief Handles execution of the command function.
   * @param in Input stream
   * @param out Output stream
   * @param tokens Parameters
   * @return Exit code of command
   *
   * The first element of the tokens vector contains the name of the command
   * being executed (as per argv convention).
   */
  inline int handleCmdFunc(std::istream &in, std::ostream &out,
                           std::vector<std::string> &tokens) const
  {
    return m_handlerFunc(in, out, tokens);
  }

private:
  const std::string m_commandName;
  const CMDHandlerFunc m_handlerFunc;
  const std::string m_description;
};

typedef std::shared_ptr<Command> Command_ptr;
typedef std::shared_ptr<const Command> Command_const_ptr;
}
