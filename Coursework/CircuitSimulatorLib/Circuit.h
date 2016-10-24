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
  static const std::string INPUT_BUS_NAME;
  static const std::string OUTPUT_BUS_NAME;

public:
  Circuit(std::vector<std::string> inputs, std::vector<std::string> outputs);
  virtual ~Circuit();

  virtual void addComponent(Component_ptr component);
  virtual bool removeComponent(const std::string &id);

  bool hasComponent(const std::string &name) const;

  Component_ptr component(const std::string &name);
  Component_const_ptr component(const std::string &name) const;

  /**
   * @brief Gets a const iterator to the start of the list of components.
   * @return Const component iterator
   */
  inline ComponentList_const_iter componentsBegin() const
  {
    return m_components.cbegin();
  }

  /**
   * @brief Gets a const iterator to the end of the list of components.
   * @return Const component iterator
   */
  inline ComponentList_const_iter componentsEnd() const
  {
    return m_components.cend();
  }

  virtual void attachWire(const std::string &from, const std::string &to);
  virtual void removeWire(const std::string &from, const std::string &to);

  bool validate() const;

  virtual void setInput(const std::string &name, bool value);
  virtual bool getInput(const std::string &name) const;
  virtual bool getOutput(const std::string &name) const;

  friend std::ostream &operator<<(std::ostream &stream, const Circuit &o);

private:
  Pin_ptr findPatchEndpoint(const std::string &def);

private:
  ComponentList m_components; //!< List of components in circuit
};
}
