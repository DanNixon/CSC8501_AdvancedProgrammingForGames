/** @file */

#pragma once

#include <vector>

namespace Coursework2
{
class BitStreamComparator
{
public:
  typedef std::vector<bool> BitStream;

public:
  static size_t Compare(const BitStream &a, const BitStream &b);
  static size_t Compare(const std::string &aFilename, const std::string &bFilename);

  static bool CompareMultiple(const std::vector<BitStream> &data);
  static bool CompareMultiple(const std::vector<std::string> &filenames);
};
}