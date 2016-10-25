/** @file */

#pragma once

#include <vector>

#include "CircuitSimulatorLib/Circuit_fwd.h"
#include "CircuitSimulatorLib/Wire.h"

namespace Coursework1
{
class Permutation
{
public:
  static size_t GenerateAllStrict(std::vector<Permutation> &results,
                                  const CircuitSimulator::WireDefList &wires,
                                  size_t connectivity = 1);

public:
  Permutation();
  virtual ~Permutation();

  void apply(CircuitSimulator::Circuit_ptr c);

  friend std::ostream &operator<<(std::ostream &stream, const Permutation &o);

private:
  CircuitSimulator::WireDefList m_wiring;
};
}