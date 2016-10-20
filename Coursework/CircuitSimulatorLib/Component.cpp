/** @file */

#pragma once

#include "Component.h"

#include <algorithm>

namespace CircuitSimulator
{
/**
 * @brief Creates a new component
 * @param id Unique string ID
 * @param name Per component name
 * @param inputs List of names of input pins
 * @param outputs List of names of output pins
 */
Component::Component(const std::string &id, const std::string &name,
                     std::vector<std::string> inputs,
                     std::vector<std::string> outputs)
    : m_id(id)
    , m_name(name)
{
  for (auto it = inputs.begin(); it != inputs.end(); ++it)
  {
    Pin *p = new Pin(*it, PIN_FLAG_INPUT);
    p->setOnChange([this]() { this->operate(); });
    m_pins.push_back(p);
  }

  for (auto it = outputs.begin(); it != outputs.end(); ++it)
    m_pins.push_back(new Pin(*it, PIN_FLAG_OUTPUT));
}

Component::~Component()
{
}

/**
 * @brief Gets a Pin from the component.
 * @param name Unique name of the pin
 * @return Pointer to the Pin
 */
Pin *Component::pin(const std::string &name)
{
  auto it = std::find_if(m_pins.begin(), m_pins.end(),
                         [name](Pin *p) { return p->id() == name; });

  if (it == m_pins.end())
    throw std::runtime_error("Cannot find pin \"" + name + "\"");

  return *it;
}

/**
 * @brief Gets a Pin from the component.
 * @param name Unique name of the pin
 * @return Const pointer to the Pin
 */
const Pin *Component::pin(const std::string &name) const
{
  auto it = std::find_if(m_pins.cbegin(), m_pins.cend(),
                         [name](Pin *p) { return p->id() == name; });

  if (it == m_pins.cend())
    throw std::runtime_error("Cannot find pin \"" + name + "\"");

  return *it;
}

/**
 * @brief Checks if a Pin with a given name and IO flags exists on this
 *        component.
 * @param name Unique name of the pin
 * @param flag Pin flags
 * @return True if a pin with the given name and flags exists
 */
bool Component::hasPin(const std::string &name, uint8_t flag) const
{
  return std::find_if(m_pins.begin(), m_pins.end(), [name, flag](Pin *p) {
           return p->id() == name && p->flags() & flag;
         }) != m_pins.end();
}

/**
 * @brief Sets the value of an input pin.
 * @param name Input name
 * @param value Value
 */
void Component::setInput(const std::string &name, bool value)
{
  Pin *p = pin(name);
  if (!(p->flags() & PIN_FLAG_INPUT))
    throw std::runtime_error("Pin \"" + name + "\" is not an input pin.");

  p->setState(value);
}

/**
 * @brief Gets the value of an input pin.
 * @param name Input name
 * @return Value
 */
bool Component::getInput(const std::string &name) const
{
  const Pin *p = pin(name);
  if (!(p->flags() & PIN_FLAG_INPUT))
    throw std::runtime_error("Pin \"" + name + "\" is not an output pin.");

  return p->getState();
}

/**
 * @brief Gets the value of an output pin.
 * @param name Input name
 * @return Value
 */
bool Component::getOutput(const std::string &name) const
{
  const Pin *p = pin(name);
  if (!(p->flags() & PIN_FLAG_OUTPUT))
    throw std::runtime_error("Pin \"" + name + "\" is not an output pin.");

  return p->getState();
}

/**
 * @brief Output a Component to a stream as a friendly formatted string.
 * @param stream Reference to output stream
 * @param o Component to output
 * @return Reference to output stream
 */
std::ostream &operator<<(std::ostream &stream, const Component &o)
{
  stream << "Component[" << o.m_name << ", id=" << o.m_id << "]";
  return stream;
}
}
