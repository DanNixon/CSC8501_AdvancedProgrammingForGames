#pragma once

#include <stdint.h>
#include <vector>
#include <string>

#include "Device.h"
#include "Patch.h"

template <typename T>
class Circuit : public Device<T>
{
public:
  Circuit(const std::string &id, const std::string &name, std::list<std::string> inputs, std::list<std::string> outputs)
    : Device<T>(id, name, inputs, outputs)
  {
  }

  virtual ~Circuit()
  {
  }

  void patch(const std::string &from, const std::string &to)
  {
    // TODO
  }

  virtual void operate()
  {
    // TOOD
  }

private:
  std::vector<Device<T> *> m_devices;
  std::vector<Patch<T> *> m_patchPanel;
};
