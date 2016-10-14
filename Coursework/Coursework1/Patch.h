#pragma once

#include <string>

#include "Device.h"

template <typename T> class Patch
{
public:
  Patch(const std::string &toStr, const std::string &fromStr,
        std::vector<Device<T> *> &devices)
  {
    // TODO
  }

  virtual ~Patch()
  {
  }

  inline Device<T> *source() const
  {
    return m_source;
  }

  inline Device<T> *destination() const
  {
    return m_destination;
  }

  inline std::string sourceOutputName() const
  {
    return m_sourceOutputName;
  }

  inline std::string destinationInputName() const
  {
    return m_destinationInputName;
  }

private:
  Device<T> *findDevice()
  {
    // TOOD
    return nullptr;
  }

private:
  const Device<T> *m_source;
  const Device<T> *m_destination;
  const std::string m_sourceOutputName;
  const std::string m_destinationInputName;
};