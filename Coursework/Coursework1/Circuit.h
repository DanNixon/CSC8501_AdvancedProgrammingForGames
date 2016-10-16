#pragma once

#include <list>
#include <string>
#include <vector>

#include "Component.h"
#include "Wire.h"

class Circuit
{
public:
  Circuit(std::list<std::string> inputs, std::list<std::string> outputs);
  virtual ~Circuit();

  inline void addComponent(Component *component)
  {
    m_components.push_back(component);
  }

  void patch(const std::string &from, const std::string &to);

  friend std::ostream &operator<<(std::ostream &stream, const Circuit &o);

private:
  std::pair<Component *, Pin *> findPatchEndpoint(const std::string &def);

private:
  std::vector<Component *> m_components;
  std::vector<Wire *> m_wiring;
};
