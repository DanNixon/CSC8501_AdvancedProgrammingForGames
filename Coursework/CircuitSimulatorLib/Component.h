/** @file */

#pragma once

#include <string>
#include <vector>

#include "Pin_fwd.h"

namespace CircuitSimulator
{
/**
 * @class Component
 * @author Dan Nixon
 * @brief Abstract class representing a component in a Circuit.
 */
class Component
{
public:
  Component(const std::string &id, const std::string &name,
            std::vector<std::string> inputs, std::vector<std::string> outputs);
  virtual ~Component();

  /**
   * @brief Gets the string ID of the pin.
   * @return String ID
   */
  inline virtual std::string id() const
  {
    return m_id;
  }

  /**
   * @brief Gets the name of the component.
   * @return Component name
   */
  inline virtual std::string name() const
  {
    return m_name;
  }

  bool hasPin(const std::string &name, uint8_t flag) const;

  Pin_ptr pin(const std::string &name);
  Pin_const_ptr Component::pin(const std::string &name) const;

  inline PinList_const_iter pinsBegin() const
  {
    return m_pins.cbegin();
  }

  inline PinList_const_iter pinsEnd() const
  {
    return m_pins.cend();
  }

  void setInput(const std::string &name, bool value);
  bool getInput(const std::string &name) const;
  bool getOutput(const std::string &name) const;

  /**
   * @brief Performs the operations required by the component.
   */
  virtual void operate() = 0;

  friend std::ostream &operator<<(std::ostream &stream, const Component &o);

protected:
  friend class Pin;
  const std::string m_id;   //!< Unique string ID
  const std::string m_name; //!< Per component name
  PinList m_pins;           //!< Vector of IO pins
};
}
