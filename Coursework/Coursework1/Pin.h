#pragma once

#include <string>

#define PIN_FLAG_INPUT 0x01
#define PIN_FLAG_OUTPUT 0x02

class Pin
{
public:
  Pin(const std::string &id, uint8_t flags);
  virtual ~Pin();

  inline std::string id() const
  {
    return m_id;
  }

  bool isInput() const;
  bool isOutput() const;

  void setState(bool state);

  inline bool getState() const
  {
    return m_state;
  }

private:
  const std::string m_id;
  const uint8_t m_flags;
  bool m_state;
};
