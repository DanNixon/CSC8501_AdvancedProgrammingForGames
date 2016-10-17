#pragma once

#include "Component.h"

#include <algorithm>

namespace CircuitSimulator
{
Component::Component(const std::string &id, const std::string &name,
                     std::list<std::string> inputs,
                     std::list<std::string> outputs)
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

Pin *Component::pin(const std::string &name)
{
  auto it = std::find_if(m_pins.begin(), m_pins.end(),
                         [name](Pin *p) { return p->id() == name; });

  if (it == m_pins.end())
    throw std::runtime_error("Cannot find pin \"" + name + "\"");

  return *it;
}

const Pin *Component::pin(const std::string &name) const
{
  auto it = std::find_if(m_pins.cbegin(), m_pins.cend(),
                         [name](Pin *p) { return p->id() == name; });

  if (it == m_pins.cend())
    throw std::runtime_error("Cannot find pin \"" + name + "\"");

  return *it;
}

bool Component::hasPin(const std::string &name, uint8_t flag) const
{
  return std::find_if(m_pins.begin(), m_pins.end(), [name, flag](Pin *p) {
           return p->id() == name && p->flags() & flag;
         }) != m_pins.end();
}

void Component::setInput(const std::string &name, bool value)
{
  Pin *p = pin(name);
  if (!(p->flags() & PIN_FLAG_INPUT))
    throw std::runtime_error("Pin \"" + name + "\" is not an input pin.");

  p->setState(value);
}

bool Component::getOutput(const std::string &name) const
{
  const Pin *p = pin(name);
  if (!(p->flags() & PIN_FLAG_OUTPUT))
    throw std::runtime_error("Pin \"" + name + "\" is not an input pin.");

  return p->getState();
}

std::ostream &operator<<(std::ostream &stream, const Component &o)
{
  stream << "Component[" << o.m_name << ", id=" << o.m_id << "]";
  return stream;
}
}