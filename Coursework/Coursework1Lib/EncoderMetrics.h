/** @file */

#pragma once

#include "CircuitSimulatorLib/BitStream.h"
#include "CircuitSimulatorLib/Encoder.h"

namespace Coursework1
{
class EncoderMetrics
{
public:
  static void GenerateRandomData(CircuitSimulator::BitStream &out, size_t len);

public:
  EncoderMetrics(CircuitSimulator::Encoder_ptr encoder);
  virtual ~EncoderMetrics();

  void measure(const CircuitSimulator::BitStream &data);

private:
  CircuitSimulator::Encoder_ptr m_encoder;
};
}