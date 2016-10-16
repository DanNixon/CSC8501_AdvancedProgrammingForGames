#pragma once

#include "Component.h"

class XORGate : public Component
{
public:
  XORGate(const std::string &id);
  virtual ~XORGate();

  virtual void operate();
};