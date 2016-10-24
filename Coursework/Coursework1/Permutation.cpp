/** @file */

#include "Permutation.h"

#include "CircuitSimulatorLib/Circuit.h"

using namespace CircuitSimulator;

size_t Permutation::GenerateAll(std::vector<Permutation>, CircuitSimulator::Circuit_const_ptr c)
{
  // TODO
  return 0;
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