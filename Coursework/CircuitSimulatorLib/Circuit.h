/** @file */

#pragma once

#include <string>
#include <vector>

#include "Component.h"

namespace CircuitSimulator
{
class Circuit
{
public:
  Circuit(std::vector<std::string> inputs, std::vector<std::string> outputs);
  virtual ~Circuit();

  virtual void addComponent(Component *component);
  Component *component(const std::string &name);
  const Component *component(const std::string &name) const;
  bool hasComponent(const std::string &name) const;

  virtual void wireUp(const std::string &from, const std::string &to);

  virtual void setInput(const std::string &name, bool value);
  virtual bool getInput(const std::string &name) const;
  virtual bool getOutput(const std::string &name) const;

  friend std::ostream &operator<<(std::ostream &stream, const Circuit &o);

private:
  Pin *findPatchEndpoint(const std::string &def);

private:
  std::vector<Component *> m_components;
};
}
