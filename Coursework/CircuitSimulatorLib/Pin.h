/** @file */

#pragma once

#include <functional>
#include <string>
#include <vector>

#define PIN_FLAG_INPUT 0x01
#define PIN_FLAG_OUTPUT 0x02

namespace CircuitSimulator
{
/**
 * @class Pin
 * @author Dan Nixon
 * @brief Stores state and connections of a pin of a Component.
 */
class Pin
{
public:
  Pin(const std::string &id, uint8_t flags);
  virtual ~Pin();

  /**
   * @brief Gets the string ID of the pin.
   * @return String ID
   */
  inline std::string id() const
  {
    return m_id;
  }

  /**
   * @brief Gets the IO flags of the pin.
   * @return IO flags
   */
  inline uint8_t flags() const
  {
    return m_flags;
  }

  bool isInput() const;
  bool isOutput() const;

  void wireTo(Pin *other);
  void setOnChange(std::function<void(void)> func);

  void setState(bool state);

  /**
   * @brief Gets the state of the pin.
   * @return State value
   */
  inline bool getState() const
  {
    return m_state;
  }

private:
  const std::string m_id;
  const uint8_t m_flags;
  bool m_state;
  std::vector<Pin *> m_outboundConnections;
  std::function<void(void)> m_onChange;
};
}
