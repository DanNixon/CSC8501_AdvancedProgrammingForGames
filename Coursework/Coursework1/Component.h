#pragma once

#include "IComponent.h"

#include <list>

#include "Pin.h"

class Component : public IComponent
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

  bool hasInput(const std::string &name) const;
  bool hasOutput(const std::string &name) const;

  void setInput(const std::string &name, bool value);
  bool getOutput(const std::string &name) const;

  virtual void operate() = 0;

protected:
  const std::string m_id;
  const std::string m_name;
  std::list<Pin *> m_pins;
};