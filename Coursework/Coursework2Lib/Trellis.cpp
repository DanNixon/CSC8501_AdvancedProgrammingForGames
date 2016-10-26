/** @file */

#include "Trellis.h"

#include <fstream>
#include <regex>

namespace Coursework2
{
/**
 * @brief Loads a Trellis from a file.
 * @param filename Name of file to load from
 * @return Loaded Trellis
 */
Trellis Trellis::LoadFromFile(const std::string &filename)
{
  std::ifstream in;
  in.open(filename, std::fstream::in);

  Trellis t;
  in >> t;

  in.close();

  return t;
}

/**
 * @brief Creates a new Trellis with a given set of mappings.
 * @param mapping Trellis mappings
 */
Trellis::Trellis(const std::vector<TrellisMapping> &mapping)
    : m_mapping(mapping)
{
}

Trellis::~Trellis()
{
}

/**
 * @brief Output a Trellis to a stream as a friendly formatted string.
 * @param stream Reference to output stream
 * @param o Trellis to output
 * @return Reference to output stream
 */
std::ostream &operator<<(std::ostream &stream, const Trellis &o)
{
  for (auto it = o.m_mapping.cbegin(); it != o.m_mapping.cend(); ++it)
    stream << it->srcState << " - " << it->bit << '/' << it->code << " - " << it->destState << '\n';

  return stream;
}

/**
 * @brief Parse a Trellis mapping from a stream.
 * @param stream Reference to input stream
 * @param o Trellis to parse
 * @return Reference to input stream
 */
std::istream &operator>>(std::istream &stream, Trellis &o)
{
  std::string line;
  while (std::getline(stream, line))
  {
    std::regex mappingRegex("(\\d+) - ([0,1])\\/([0,1][0,1]) - (\\d+)");
    std::smatch match;

    if (std::regex_match(line, match, mappingRegex))
    {
      TrellisMapping m;

      m.srcState = std::stoul(match[1]);
      m.bit = match[2] == "1";
      m.code = match[3];
      m.destState = std::stoul(match[4]);

      o.m_mapping.push_back(m);
    }
  }

  return stream;
}
}