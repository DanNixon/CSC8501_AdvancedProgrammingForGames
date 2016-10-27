/** @file */

#include "Encoder.h"

#include <map>
#include <sstream>

namespace CircuitSimulator
{
/**
 * @brief Creates a new encoder.
 *
 * CReates a Circuit with a single bit on the input bus and two bits on the
 * output bus.
 */
Encoder::Encoder()
    : Circuit({"bit_0"}, {"bit_0", "bit_1"})
{
}

Encoder::~Encoder()
{
}

/**
 * @copydoc Circuit::addComponent
 */
void Encoder::addComponent(Component_ptr component)
{
  Circuit::addComponent(component);

  RegisterArray_ptr ra = std::dynamic_pointer_cast<RegisterArray>(component);
  if (ra != nullptr)
    m_registers.push_back(ra);
}

/**
 * @brief Checks to ensure that all components in this Circuit are used.
 * @return True if all components are used
 * @see Component::hasLogicalConnection()
 */
bool Encoder::validateComponentUse()
{
  for (auto it = m_components.cbegin(); it != m_components.cend(); ++it)
  {
    if (!(*it)->hasLogicalConnection())
      return false;
  }

  return true;
}

/**
 * @brief Shifts all registers in the encoder.
 * @param direction Direction to shift in (-1 for left, 1 for right)
 */
void Encoder::advanceRegisters(int8_t direction)
{
  for (auto it = m_registers.begin(); it != m_registers.end(); ++it)
  {
    switch (direction)
    {
    case -1:
      (*it)->shiftLeft();
      break;
    case 1:
      (*it)->shiftRight();
      break;
    default:
      throw std::runtime_error("Invalid shift direction");
    }
  }
}

/**
 * @brief Resets all registers to all zeros.
 */
void Encoder::resetRegisters()
{
  for (auto it = m_registers.begin(); it != m_registers.end(); ++it)
    (*it)->reset();
}

/**
 * @brief Encodes a string of bits.
 * @param in Input data
 * @param out Output data
 */
void Encoder::encode(const BitStream &in, BitStream &out)
{
  for (auto it = in.cbegin(); it != in.cend(); ++it)
  {
    setInput("bit_0", *it);
    out.push_back(getOutput("bit_0"));
    out.push_back(getOutput("bit_1"));
    advanceRegisters(-1);
  }
}

/**
 * @brief Generates a Trellis for decoding output from this encoder.
 * @return Trellis describing the state transitions of this encoder
 */
Trellis Encoder::generateTrellis()
{
  // Sanity check (logic only implemented for a single register)
  if (m_registers.size() != 1)
    throw std::runtime_error("Incorrect number of registers (trellis generation needs exactly one "
                             "register in an encoder).");

  size_t numElements = m_registers[0]->size() - 1;
  size_t numStates = (size_t)std::pow(2, numElements);

  // Generate all state permutations
  std::vector<BitStream> states;
  states.reserve(numStates);
  for (size_t i = 0; i < numStates; i++)
  {
    states.push_back(BitStream(numElements));

    for (size_t j = 0; j < numElements; j++)
      states[i][numElements - 1 - j] = (i & ((size_t)0x1 << j)) > 0;
  }

  // Test all input
  std::vector<TrellisMapping> mappings;
  for (size_t i = 0; i < numStates * 2; i++)
  {
    size_t srcIdx = i % numStates;
    bool testBit = i / numStates == 0;

    // Set register elements (exclude first as it is a mirror of the input bit)
    for (size_t j = 0; j < numElements; j++)
      m_registers[0]->setInput("bit_" + std::to_string(j + 1), states[srcIdx][j]);

    // Run encoder step
    setInput("bit_0", testBit);
    std::stringstream resStr;
    resStr << getOutput("bit_0") << getOutput("bit_1");
    advanceRegisters(-1);

    // Get register state
    BitStream outState;
    for (size_t j = 0; j < numElements; j++)
      outState.push_back(m_registers[0]->getOutput("bit_" + std::to_string(j + 1)));

    // Find output state index
    auto it = std::find(states.begin(), states.end(), outState);
    if (it == states.end())
      throw std::runtime_error("Could not find state.");
    size_t destIdx = it - states.begin();

    mappings.push_back({srcIdx, testBit, resStr.str(), destIdx});
  }

  return Trellis(mappings);
}
}
