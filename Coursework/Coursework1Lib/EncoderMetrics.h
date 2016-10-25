/** @file */

#pragma once

#include <map>

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
  void resetStats();

  friend std::ostream &operator<<(std::ostream &stream, const EncoderMetrics &o);

private:
  CircuitSimulator::Encoder_ptr m_encoder;
  std::map<std::string, std::map<std::string, double>> m_stats;
};
}