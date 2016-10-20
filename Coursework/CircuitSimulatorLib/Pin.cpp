/** @file */

#include "Pin.h"

#include <algorithm>

namespace CircuitSimulator
{
/**
 * @brief Create a new pin.
 * @param id String ID of the pin
 * @param flags IO flags
 */
Pin::Pin(const std::string &id, uint8_t flags)
    : m_id(id)
    , m_flags(flags)
    , m_state(false)
    , m_onChange([]()
                 {
                 })
{
}

Pin::~Pin()
{
}

/**
 * @brief Checks if this pin is an input.
 * @return True if PIN_FLAG_INPUT is set
 */
bool Pin::isInput() const
{
  return (m_flags & PIN_FLAG_INPUT) > 0;
}

/**
 * @brief Checks if this pin is an output.
 * @return True if PIN_FLAG_OUTPUT is set
 */
bool Pin::isOutput() const
{
  return (m_flags & PIN_FLAG_OUTPUT) > 0;
}

/**
 * @brief Wires this pin to another pin.
 * @param other Other pin to wire to
 */
void Pin::wireTo(Pin *other)
{
  if (!((PIN_FLAG_INPUT | PIN_FLAG_OUTPUT) & (m_flags | other->m_flags)))
    throw std::runtime_error("Wire has no directionality");

  m_outboundConnections.push_back(other);
  other->m_inboundConnections.push_back(this);
}

/**
 * @brief Sets the function to be called when the value of this pin changes.
 * @param func Function
 */
void Pin::setOnChange(std::function<void(void)> func)
{
  m_onChange = func;
}

/**
 * @brief Sets the state of this pin.
 * @param state New state
 */
void Pin::setState(bool state)
{
  m_state = state;

  /* Set state of outbound connections */
  for (auto it = m_outboundConnections.begin();
       it != m_outboundConnections.end(); ++it)
    (*it)->setState(m_state);

  m_onChange();
}
}
