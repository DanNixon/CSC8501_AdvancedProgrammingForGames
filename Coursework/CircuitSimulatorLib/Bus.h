/** @file */

#pragma once

#include "Component.h"

#include "Pin.h"

namespace CircuitSimulator
{
/**
 * @class Bus
 * @author Dan Nixon
 * @brief Provides a method of inserting and extracting pin states from a
 *        Circuit.
 */
class Bus : public Component
{
public:
  /**
   * @brief Creates a new IO bus.
   * @param id String ID
   * @param ioNames List if IO pin names
   */
  Bus(const std::string &id, std::vector<std::string> ioNames)
      : Component(id, "Bus", {}, {})
  {
    for (auto it = ioNames.begin(); it != ioNames.end(); ++it)
      m_pins.push_back(Pin_ptr(new Pin(this, *it, PIN_FLAG_OUTPUT | PIN_FLAG_INPUT)));
  }

  virtual ~Bus()
  {
  }

  /**
   * @copydoc Component::operate
   */
  virtual void operate()
  {
    /* Nothing to do here */
  }
};

typedef std::shared_ptr<Bus> Bus_ptr;
typedef std::shared_ptr<const Bus> Bus_const_ptr;
}
