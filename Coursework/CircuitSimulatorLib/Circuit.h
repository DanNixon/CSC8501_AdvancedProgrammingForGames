/** @file */

#pragma once

#include <string>
#include <vector>

#include "Component_fwd.h"
#include "Pin_fwd.h"

namespace CircuitSimulator
{
/**
 * @class Circuit
 * @author Dan Nixon
 * @brief Stores the setup and state of a virtual circut.
 */
class Circuit
{
public:
  Circuit(std::vector<std::string> inputs, std::vector<std::string> outputs);
  virtual ~Circuit();

  virtual void addComponent(Component_ptr component);
  Component_ptr component(const std::string &name);
  Component_const_ptr component(const std::string &name) const;
  bool hasComponent(const std::string &name) const;

  virtual void wireUp(const std::string &from, const std::string &to);
  bool validate() const;

  virtual void setInput(const std::string &name, bool value);
  virtual bool getInput(const std::string &name) const;
  virtual bool getOutput(const std::string &name) const;

  friend std::ostream &operator<<(std::ostream &stream, const Circuit &o);

private:
  Pin_ptr findPatchEndpoint(const std::string &def);

private:
  std::vector<Component_ptr> m_components;
};
}
