/** @file */

#include "Pin.h"

#include <algorithm>

#include "Component.h"

namespace CircuitSimulator
{
/**
 * @brief Attaches a wire between two pins.
 * @param source Source (output) pin
 * @param dest Destination (input) pin
 */
void Pin::AttachWire(Pin_ptr source, Pin_ptr dest)
{
  if (!((PIN_FLAG_INPUT | PIN_FLAG_OUTPUT) & (source->m_flags | dest->m_flags)))
    throw std::runtime_error("Wire has no directionality");

  source->m_outboundConnections.push_back(dest);
  dest->m_inboundConnections.push_back(source);
}

/**
 * @brief Removes and existing wire between two pins.
 * @param source Source (output) pin
 * @param dest Destination (input) pin
 */
void Pin::RemoveWire(Pin_ptr source, Pin_ptr dest)
{
  auto destIt =
      std::find(dest->m_inboundConnections.begin(), dest->m_inboundConnections.end(), source);

  auto sourceIt =
      std::find(source->m_outboundConnections.begin(), source->m_outboundConnections.end(), dest);

  if (destIt != dest->m_inboundConnections.end() && sourceIt != source->m_outboundConnections.end())
  {
    dest->m_inboundConnections.erase(destIt);
    source->m_outboundConnections.erase(sourceIt);
  }
}

/**
*@brief Create a new pin.
*@param parent Pointer to the parent component
*@param id String ID of the pin
*@param flags IO flags
*/
Pin::Pin(Component *parent, const std::string &id, uint8_t flags)
    : m_parentComponent(parent)
    , m_id(id)
    , m_flags(flags)
    , m_state(false)
    , m_onChange([]() {})
{
}

Pin::~Pin()
{
  m_inboundConnections.clear();
  m_outboundConnections.clear();
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
  for (auto it = m_outboundConnections.begin(); it != m_outboundConnections.end(); ++it)
    (*it)->setState(m_state);

  m_onChange();
}
}
