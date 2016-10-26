/** @file */

#include "BinaryFileIO.h"

#include <fstream>
#include <string>

using namespace CircuitSimulator;

namespace Utility
{
/**
 * @brief Reads a formatted binary string from an input stream.
 * @param bits Reference to vector to store read bits in
 * @param in Reference to stream to read from
 * @return Number of bits read
 */
size_t BinaryFileIO::Read(BitStream &bits, std::istream &in)
{
  size_t numBits = 0;
  char c;
  while (in.get(c))
  {
    switch (c)
    {
    case '0':
      bits.push_back(false);
      numBits++;
      break;
    case '1':
      bits.push_back(true);
      numBits++;
      break;
    default:
      continue;
    }
  }
  return numBits;
}

/**
 * @brief Writes a formatted binary string to an output stream.
 * @param bits Reference to vector containing bits to write
 * @param out Reference to stream to write to
 * @return Number of bits written
 */
size_t BinaryFileIO::Write(const BitStream &bits, std::ostream &out)
{
  size_t numBits = 0;
  for (auto it = bits.begin(); it != bits.end(); ++it)
  {
    out << (*it);
    numBits++;
  }
  return numBits;
}

/**
 * @brief Reads a formatted binary string from a file.
 * @param bits Reference to vector to store read bits in
 * @param filename Name of file to read from
 * @return Number of bits read
 */
size_t BinaryFileIO::ReadFile(BitStream &bits, const std::string &filename)
{
  std::ifstream in;
  in.open(filename, std::fstream::in);
  if (!in.good())
    throw std::runtime_error("Failed to open file for reading: " + filename);
  size_t res = Read(bits, in);
  in.close();
  return res;
}

/**
 * @brief Writes a formatted binary string to a file.
 * @param bits Reference to vector containing bits to write
 * @param filename Name of file to write to
 * @return Number of bits written
 */
size_t BinaryFileIO::WriteFile(const BitStream &bits, const std::string &filename)
{
  std::ofstream out;
  out.open(filename, std::fstream::out);
  size_t res = Write(bits, out);
  out.close();
  return res;
}
}
