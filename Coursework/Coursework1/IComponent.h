#pragma once

#include <string>

class IComponent
{
public:
  virtual std::string id() const = 0;
  virtual std::string name() const = 0;

  virtual bool hasInput(const std::string &name) const = 0;
  virtual bool hasOutput(const std::string &name) const = 0;

  virtual void setInput(const std::string &name, bool value) = 0;
  virtual bool getOutput(const std::string &name) const = 0;
};