#pragma once

#include <list>

#include "Pin.h"

class Component
{
public:
  Component(const std::string &id, const std::string &name,
            std::list<std::string> inputs, std::list<std::string> outputs);
  virtual ~Component();

  inline virtual std::string id() const
  {
    return m_id;
  }

  inline virtual std::string name() const
  {
    return m_name;
  }

  Pin *pin(const std::string &name);
  const Pin *Component::pin(const std::string &name) const;
  bool hasPin(const std::string &name, uint8_t flag) const;

  void setInput(const std::string &name, bool value);
  bool getOutput(const std::string &name) const;

  virtual void operate() = 0;

  friend std::ostream &operator<<(std::ostream &stream, const Component &o);

protected:
  const std::string m_id;
  const std::string m_name;
  std::list<Pin *> m_pins;
};