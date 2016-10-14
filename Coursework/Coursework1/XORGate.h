#pragma once

#include "Device.h"

class XORGate : public Device<bool>
{
public: 
  XORGate(const std::string &id);
  virtual ~XORGate();

  virtual void operate();
};