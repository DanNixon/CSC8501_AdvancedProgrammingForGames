#pragma once

#include <list>
#include <string>
#include <vector>

#include "Component.h"

namespace CircuitSimulator
{
class Circuit
{
public:
  Circuit(std::list<std::string> inputs, std::list<std::string> outputs);
  virtual ~Circuit();

  inline void addComponent(Component *component)
  {
    m_components.push_back(component);
  }

  Component *component(const std::string &name);
  const Component *component(const std::string &name) const;
  bool hasComponent(const std::string &name) const;

  void wireUp(const std::string &from, const std::string &to);

  void setInput(const std::string &name, bool value);
  bool getOutput(const std::string &name) const;

  friend std::ostream &operator<<(std::ostream &stream, const Circuit &o);

private:
  Pin *findPatchEndpoint(const std::string &def);

private:
  std::vector<Component *> m_components;
};
}