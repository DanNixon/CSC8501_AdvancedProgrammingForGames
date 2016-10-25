/** @file */

#include "PermutationGenerator.h"

using namespace CircuitSimulator;

namespace Coursework1
{
PermutationGenerator::PermutationGenerator(const CircuitSimulator::WireDefList &wires)
    : m_wires(wires)
    , m_numPermutations(2 ^ wires.size())
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
    // TODO
  }

  return Permutation(wires);
}
}