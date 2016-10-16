#pragma once

#include <ostream>

#include "Component.h"
#include "Pin.h"

class Wire
{
public:
  Wire(Component *source, Pin *output, Component *dest, Pin *input);
  virtual ~Wire();

  inline const Component *source() const
  {
    return m_source;
  }

  inline const Component *destination() const
  {
    return m_destination;
  }

  inline const Pin *output() const
  {
    return m_output;
  }

  inline const Pin *input() const
  {
    return m_input;
  }

  friend std::ostream &operator<<(std::ostream &stream, const Wire &o);

private:
  const Component *m_source;
  const Component *m_destination;
  const Pin *m_output;
  const Pin *m_input;
};