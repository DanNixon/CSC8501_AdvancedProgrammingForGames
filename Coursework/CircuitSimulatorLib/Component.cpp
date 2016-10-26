/** @file */

#pragma once

#include "Component.h"

#include <algorithm>

#include "Pin.h"

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
                     std::vector<std::string> inputs, std::vector<std::string> outputs)
    : m_id(id)
    , m_name(name)
{
  for (auto it = inputs.begin(); it != inputs.end(); ++it)
  {
    auto p = std::make_shared<Pin>(this, *it, PIN_FLAG_INPUT);
    p->setOnChange([this]() { this->operate(); });
    m_pins.push_back(p);
  }

  for (auto it = outputs.begin(); it != outputs.end(); ++it)
    m_pins.push_back(std::make_shared<Pin>(this, *it, PIN_FLAG_OUTPUT));
}

Component::~Component()
{
}

/**
 * @brief Determines of this component has sufficient connections to make a logical difference to
 *        the Circuit that contains it.
 * @param maxInputs Max number of inputs an input pin may have
 * @return True if this component is significant
 *
 * A logically significant component must have at least one input and one output pin connected.
 */
bool Component::hasLogicalConnection(size_t maxInputs) const
{
  bool connectedInput = false;
  bool connectedOutput = false;

  for (auto it = m_pins.cbegin(); it != m_pins.cend(); ++it)
  {
    if (!connectedInput && (*it)->isInput() && (*it)->numInboundConnections() > 0 &&
        (*it)->numInboundConnections() <= maxInputs)
    {
      connectedInput = true;

      // Special case for bi-directional pins
      if ((*it)->isOutput())
        connectedOutput = true;
    }

    if (!connectedOutput && (*it)->isOutput() && (*it)->numOutboundConnections() > 0)
    {
      connectedOutput = true;

      // Special case for bi-directional pins
      if ((*it)->isInput())
        connectedInput = true;
    }
  }

  return connectedInput && connectedOutput;
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
  return std::find_if(m_pins.begin(), m_pins.end(), [name, flag](Pin_ptr p) {
           return p->id() == name && p->flags() & flag;
         }) != m_pins.end();
}

/**
 * @brief Gets a Pin from the component.
 * @param name Unique name of the pin
 * @return Pointer to the Pin
 */
Pin_ptr Component::pin(const std::string &name)
{
  auto it =
      std::find_if(m_pins.begin(), m_pins.end(), [name](Pin_ptr p) { return p->id() == name; });

  if (it == m_pins.end())
    throw std::runtime_error("Cannot find pin \"" + name + "\"");

  return *it;
}

/**
 * @brief Gets a Pin from the component.
 * @param name Unique name of the pin
 * @return Const pointer to the Pin
 */
Pin_const_ptr Component::pin(const std::string &name) const
{
  auto it = std::find_if(m_pins.cbegin(), m_pins.cend(),
                         [name](Pin_const_ptr p) { return p->id() == name; });

  if (it == m_pins.cend())
    throw std::runtime_error("Cannot find pin \"" + name + "\"");

  return *it;
}

/**
 * @brief Sets the value of an input pin.
 * @param name Input name
 * @param value Value
 */
void Component::setInput(const std::string &name, bool value)
{
  Pin_ptr p = pin(name);
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
  Pin_const_ptr p = pin(name);
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
  Pin_const_ptr p = pin(name);
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
