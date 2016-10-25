/** @file */

#include "PermutationGenerator.h"

using namespace CircuitSimulator;

namespace Coursework1
{
PermutationGenerator::PermutationGenerator(const CircuitSimulator::WireDefList &wires)
    : m_wires(wires)
    , m_numPermutations((size_t)std::pow(2, wires.size()))
{
}

PermutationGenerator::~PermutationGenerator()
{
}

Permutation PermutationGenerator::permutation(size_t mask)
{
  WireDefList wires;

  for (size_t i = 0; i < m_wires.size(); i++)
  {
    size_t m = (size_t)0x1 << i;
    size_t mm = mask & m;
    if (mm > 0)
      wires.push_back(m_wires[i]);
  }

  return Permutation(wires);
}
}