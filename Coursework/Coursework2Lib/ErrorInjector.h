/** @file */

#pragma once

#include "CircuitSimulatorLib/BitStream.h"

namespace Coursework2
{
class ErrorInjector
{
public:
  static const size_t BURST_RAND_MAX;
  static const size_t BURST_RAND_THRESHOLD;
  static const size_t BURST_LENGTH;

public:
  static void InjectError(const CircuitSimulator::BitStream &in, CircuitSimulator::BitStream &out);
};
}