#pragma once

#include <functional>
#include <string>
#include <vector>

class CLICommand
{
public:
  typedef std::function<int(std::istream &in, std::ostream &out,
                            std::vector<std::string>)>
      CMDHandlerFunc;

public:
  CLICommand(const std::string &commandName, CMDHandlerFunc func,
             const std::string &desc = "")
      : m_commandName(commandName)
      , m_handlerFunc(func)
      , m_description(desc)
  {
  }

  virtual ~CLICommand()
  {
  }

  inline std::string commandName() const
  {
    return m_commandName;
  }

  inline std::string description() const
  {
    return m_description;
  }

  inline int handle(std::istream &in, std::ostream &out,
                    std::vector<std::string> tokens) const
  {
    return m_handlerFunc(in, out, tokens);
  }

private:
  const std::string m_commandName;
  const CMDHandlerFunc m_handlerFunc;
  const std::string m_description;
};
