#pragma once

#include <ostream>

#include "IComponent.h"
#include "Pin.h"

class Wire
{
public:
  Wire(IComponent *source, Pin *output, IComponent *dest, Pin *input);
  virtual ~Wire();

  inline const IComponent *source() const
  {
    return m_source;
  }

  inline const IComponent *destination() const
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
  const IComponent *m_source;
  const IComponent *m_destination;
  const Pin *m_output;
  const Pin *m_input;
};