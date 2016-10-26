/** @file */

#include "Permutation.h"

#include "CircuitSimulatorLib/Circuit.h"

using namespace CircuitSimulator;

namespace Coursework1
{
/**
 * @brief Creates a new Permutation.
 * @param wires List of wires
 */
Permutation::Permutation(const WireDefList &wires)
    : m_wires(wires)
{
}

/**
 * @brief Copies a permutation.
 * @param other Permutation to copy.
 */
Permutation::Permutation(const Permutation &other)
    : m_wires(other.m_wires)
{
}

Permutation::~Permutation()
{
}

/**
 * @brief Applies the wiring of this permutation to a circuit.
 * @param c Circuit to apply wiring to
 */
void Permutation::apply(CircuitSimulator::Circuit_ptr c)
{
  for (auto it = m_wires.cbegin(); it != m_wires.cend(); ++it)
    c->attachWire(it->first, it->second);
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

  for (auto it = o.m_wires.begin(); it != o.m_wires.end(); ++it)
    stream << it->first << " -> " << it->second << '\n';

  stream << ']';

  return stream;
}
}
