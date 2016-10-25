/** @file */

#pragma once

#include "Component.h"

#include "Pin.h"

namespace CircuitSimulator
{
/**
 * @class RegisterArray
 * @author Dan Nixon
 * @brief Represents an array of bits in a register with shifting functionality.
 */
class RegisterArray : public Component
{
public:
  /**
   * @brief Creates a new register array of a given number of bits.
   * @param id String ID
   * @param numElements NUmber of register bit positions
   */
  RegisterArray(const std::string &id, size_t numElements)
      : Component(id, "Register Array", {}, {})
  {
    for (size_t i = 0; i < numElements; i++)
      m_pins.push_back(
          Pin_ptr(new Pin(this, ("bit_" + std::to_string(i)), PIN_FLAG_OUTPUT | PIN_FLAG_INPUT)));
  }

  virtual ~RegisterArray()
  {
  }

  /**
   * @copydoc Component::operate
   */
  virtual void operate()
  {
    /* Nothing to do here */
  }

  /**
   * @brief Performs a bit shift left.
   */
  void shiftLeft()
  {
    if (m_pins.size() < 2)
      throw std::runtime_error("Cannot shift less than 2 bits");

    for (size_t i = m_pins.size() - 1; i > 0; i--)
      m_pins[i]->setState(m_pins[i - 1]->getState());

    m_pins.front()->setState(false);
  }

  /**
   * @brief Performs a bit shift right.
   */
  void shiftRight()
  {
    if (m_pins.size() < 2)
      throw std::runtime_error("Cannot shift less than 2 bits");

    for (size_t i = 0; i < m_pins.size() - 1; i++)
      m_pins[i]->setState(m_pins[i + 1]->getState());

    m_pins.back()->setState(false);
  }

  void reset()
  {
    for (auto it = m_pins.begin(); it != m_pins.end(); ++it)
      (*it)->setState(false);
  }
};

typedef std::shared_ptr<RegisterArray> RegisterArray_ptr;
typedef std::shared_ptr<const RegisterArray> RegisterArray_const_ptr;
}
