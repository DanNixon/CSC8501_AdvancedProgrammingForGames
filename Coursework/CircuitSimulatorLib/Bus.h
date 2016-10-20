/** @file */

#pragma once

#include "Component.h"

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
      m_pins.push_back(new Pin(*it, PIN_FLAG_OUTPUT | PIN_FLAG_INPUT));
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
}
