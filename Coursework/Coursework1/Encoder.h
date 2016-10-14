#pragma once

#include "Circuit.h"

class Encoder : public Circuit<bool>
{
public:
  Encoder(const std::string &id)
      : Circuit(id, "Encoder", {"input_bit"}, {"output_bit_1", "output_bit_2"})
  {
  }

  ~Encoder()
  {
  }
};