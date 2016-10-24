/** @file */

#pragma once

#include <functional>
#include <string>
#include <vector>

#include "Component_fwd.h"
#include "Pin_fwd.h"

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
  static void AttachWire(Pin_ptr source, Pin_ptr dest);
  static void RemoveWire(Pin_ptr source, Pin_ptr dest);

public:
  Pin(Component *parent, const std::string &id, uint8_t flags);
  virtual ~Pin();

  /**
   * @brief Gets a pointer to the component that owns this pin.
   * @return Pointer to parent component
   *
   * Ownership is never transfered using this function, the Component pointed to
   * should not be deleted.
   */
  Component *parentComponent() const
  {
    return m_parentComponent;
  }

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

  /**
   * @brief Gets a const iterator to the start of the list of inbound connecting pins.
   * @return Const pin iterator
   */
  inline PinList_const_iter inboundConnectionsBegin() const
  {
    return m_inboundConnections.cbegin();
  }

  /**
   * @brief Gets a const iterator to the end of the list of inbound connecting pins.
   * @return Const pin iterator
   */
  inline PinList_const_iter inboundConnectionsEnd() const
  {
    return m_inboundConnections.cend();
  }

  /**
   * @brief Gets a const iterator to the start of the list of outbound connecting pins.
   * @return Const pin iterator
   */
  inline PinList_const_iter outboundConnectionsBegin() const
  {
    return m_outboundConnections.cbegin();
  }

  /**
   * @brief Gets a const iterator to the end of the list of outbound connecting pins.
   * @return Const pin iterator
   */
  inline PinList_const_iter outboundConnectionsEnd() const
  {
    return m_outboundConnections.cend();
  }

private:
  Component *m_parentComponent;         //!< Pointer to parent component
  const std::string m_id;               //!< Unique string ID
  const uint8_t m_flags;                //!< IO pin flags
  bool m_state;                         //!< Current pin state
  PinList m_inboundConnections;         //!< Vector of inbound connections
  PinList m_outboundConnections;        //!< Vector of outbound connections
  std::function<void(void)> m_onChange; //!< Function called when pin state is set
};
}
