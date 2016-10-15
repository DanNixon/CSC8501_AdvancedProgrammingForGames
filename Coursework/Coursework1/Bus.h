#pragma once

#include "Component.h"

class Bus : public Component
{
public:
  Bus(const std::string &id, std::list<std::string> ioNames)
      : Component(id, "Bus", {}, {})
  {
    for (auto it = ioNames.begin(); it != ioNames.end(); ++it)
      m_pins.push_back(new Pin(*it, PIN_FLAG_OUTPUT | PIN_FLAG_INPUT));
  }

  virtual ~Bus()
  {
  }

  virtual void operate()
  {
    // Nothing to do here
  }
};