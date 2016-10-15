#pragma once

#include "Circuit.h"

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