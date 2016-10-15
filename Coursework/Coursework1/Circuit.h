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

  inline void addComponent(IComponent *component)
  {
    m_components.push_back(component);
  }

  void patch(const std::string &from, const std::string &to);

private:
  std::pair<IComponent *, Pin *> findPatchEndpoint(const std::string &def);

private:
  std::vector<IComponent *> m_components;
  std::vector<Wire *> m_wiring;
};
