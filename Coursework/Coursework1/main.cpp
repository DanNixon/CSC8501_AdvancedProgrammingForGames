#include <iostream>
#include <string>
#include <vector>

#include "Encoder.h"
#include "Wire.h"
#include "XORGate.h"

int main()
{
  Encoder e;
  e.addComponent(new XORGate("xor1"));
  e.addComponent(new XORGate("xor2"));

  e.patch("input_bus.input_bit", "xor1.a");
  e.patch("input_bus.input_bit", "xor2.a");
  e.patch("xor2.z", "xor1.b");
  e.patch("xor1.z", "output_bus.output_bit_1");
  e.patch("xor2.z", "output_bus.output_bit_2");

  std::cout << e << '\n';

  return 0;
}
