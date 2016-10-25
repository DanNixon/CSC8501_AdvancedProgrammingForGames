/** @file */

#include "Permutation.h"

#include "CircuitSimulatorLib/Circuit.h"

using namespace CircuitSimulator;

namespace Coursework1
{
size_t Permutation::GenerateAllStrict(std::vector<Permutation> &results, const WireDefList &wires,
                                      size_t connectivity)
{
  size_t numPermutations = 0;
  // TOOD
  return numPermutations;
}

Permutation::Permutation()
{
}

Permutation::~Permutation()
{
}

void Permutation::apply(CircuitSimulator::Circuit_ptr c)
{
  // TODO
}

/**
 * @brief Output a Permutation to a stream as a friendly formatted string.
 * @param stream Reference to output stream
 * @param o Permutation to output
 * @return Reference to output stream
 */
std::ostream &operator<<(std::ostream &stream, const Permutation &o)
{
  stream << "Permutation[\n";

  for (auto it = o.m_wiring.begin(); it != o.m_wiring.end(); ++it)
    stream << it->first << " - " << it->second << '\n';

  stream << ']';

  return stream;
}
}