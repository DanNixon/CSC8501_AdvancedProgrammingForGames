#pragma once

#include <string>
#include <list>
#include <map>

template <typename T>
class Device
{
public:
  typedef typename std::map<std::string, T>::const_iterator IOConstListIter;

public:
  Device(const std::string &id, const std::string &name, std::list<std::string> inputs, std::list<std::string> outputs)
    : m_id(id)
    , m_name(name)
  {
    for (auto it = inputs.begin(); it != inputs.end(); ++it)
      m_inputs[*it] = T();

    for (auto it = outputs.begin(); it != outputs.end(); ++it)
      m_outputs[*it] = T();
  }

  virtual ~Device()
  {
  }

  virtual std::string id() const
  {
    return m_id;
  }

  virtual std::string name() const
  {
    return m_name;
  }

  virtual IOConstListIter inputs() const
  {
    return m_inputs.cbegin();
  }

  virtual IOConstListIter inputsEnd() const
  {
    return m_inputs.cend();
  }

  virtual IOConstListIter outputs() const
  {
    return m_outputs.cbegin();
  }

  virtual IOConstListIter outputsEnd() const
  {
    return m_outputs.cend();
  }

  void setInput(const std::string &name, T value)
  {
    m_inputs[name] = value;
  }

  virtual T getOutput(const std::string &name) const
  {
    return m_outputs.at(name);
  }

  virtual void operate() = 0;

protected:
  const std::string m_id;
  const std::string m_name;
  std::map<std::string, T> m_inputs;
  std::map<std::string, T> m_outputs;
};