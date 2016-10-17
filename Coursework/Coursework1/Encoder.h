#pragma once

#include "Circuit.h"

namespace CircuitSimulator
{
class Encoder : public Circuit
{
public:
  Encoder()
      : Circuit({"input_bit"}, {"output_bit_1", "output_bit_2"})
  {
  }

  ~Encoder()
  {
  }
};
}