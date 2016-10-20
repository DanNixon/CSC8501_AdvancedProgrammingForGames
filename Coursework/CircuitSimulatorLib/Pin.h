/** @file */

#pragma once

#include <functional>
#include <string>
#include <vector>

#define PIN_FLAG_INPUT 0x01
#define PIN_FLAG_OUTPUT 0x02

namespace CircuitSimulator
{
class Component;

/**
 * @class Pin
 * @author Dan Nixon
 * @brief Stores state and connections of a pin of a Component.
 */
class Pin
{
public:
  Pin(Component * parent, const std::string &id, uint8_t flags);
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

  bool depthFirstValidation(std::vector<Pin *> &stack, bool comp = false);

private:
  Component *m_parentComponent;       //!< Pointer to parent component
  const std::string m_id;                   //!< Unique string ID
  const uint8_t m_flags;                    //!< IO pin flags
  bool m_state;                             //!< Current pin state
  std::vector<Pin *> m_inboundConnections;  //!< Vector of inbound connections
  std::vector<Pin *> m_outboundConnections; //!< Vector of outbound connections
  std::function<void(void)>
      m_onChange; //!< Function called when pin state is set
};
}
