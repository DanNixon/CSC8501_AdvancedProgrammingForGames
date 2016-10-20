/** @file */

#include "BinaryFileIO.h"

#include <fstream>

namespace Utility
{
/**
 * @brief Reads a formatted binary string from an input stream.
 * @param bits Reference to vector to store read bits in
 * @param in Reference to stream to read from
 * @return Number of bits read
 */
size_t BinaryFileIO::Read(std::vector<bool> &bits, std::istream &in)
{
  size_t numBits = 0;
  bool b;
  while ((in >> b).good())
  {
    bits.push_back(b);
    numBits++;
  }
  return numBits;
}

/**
 * @brief Writes a formatted binary string to an output stream.
 * @param bits Reference to vector containing bits to write
 * @param in Reference to stream to write to
 * @return Number of bits written
 */
size_t BinaryFileIO::Write(const std::vector<bool> &bits, std::ostream &out)
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
size_t BinaryFileIO::ReadFile(std::vector<bool> &bits,
                              const std::string &filename)
{
  std::ifstream in;
  in.open(filename, std::fstream::in);
  return Read(bits, in);
}

/**
 * @brief Writes a formatted binary string to a file.
 * @param bits Reference to vector containing bits to write
 * @param filename Name of file to write to
 * @return Number of bits written
 */
size_t BinaryFileIO::WriteFile(const std::vector<bool> &bits,
                               const std::string &filename)
{
  std::ofstream out;
  out.open(filename, std::fstream::out);
  return Write(bits, out);
}
}