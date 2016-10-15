#pragma once

#include "Component.h"

#include <algorithm>

Component::Component(const std::string &id, const std::string &name,
                     std::list<std::string> inputs,
                     std::list<std::string> outputs)
    : IComponent()
    , m_id(id)
    , m_name(name)
{
  for (auto it = inputs.begin(); it != inputs.end(); ++it)
    m_pins.push_back(new Pin(*it, PIN_FLAG_INPUT));

  for (auto it = outputs.begin(); it != outputs.end(); ++it)
    m_pins.push_back(new Pin(*it, PIN_FLAG_OUTPUT));
}

Component::~Component()
{
}

bool Component::hasInput(const std::string &name) const
{
  return false;
}

bool Component::hasOutput(const std::string &name) const
{
  return false;
}

void Component::setInput(const std::string &name, bool value)
{
  auto it = std::find_if(m_pins.begin(), m_pins.end(),
                         [name](Pin *p) { return p->id() == name; });
  if (it == m_pins.end())
    throw std::runtime_error("Pin \"" + name + "\" of device \"" + m_id +
                             "\" not found");
  // TODO
}

bool Component::getOutput(const std::string &name) const
{
  return false;
}
