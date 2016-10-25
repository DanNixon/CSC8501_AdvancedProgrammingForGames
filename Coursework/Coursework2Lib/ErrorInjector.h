/** @file */

#pragma once

#include "CircuitSimulatorLib/BitStream.h"

namespace Coursework2
{
class ErrorInjector
{
public:
  void InjectError(const CircuitSimulator::BitStream &in, CircuitSimulator::BitStream &out);
};
}