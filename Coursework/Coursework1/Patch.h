#pragma once

#include <string>

#include "Device.h"

template <typename T>
class Patch
{
private:
  const Device<T> * m_source;
  const Device<T> * m_destination;
  const std::string m_sourceInputName;
  const std::string m_destinationOutputName;
};