/** @file */

#include "BitStreamComparator.h"

#include <algorithm>

#include "UtilityLib/BinaryFileIO.h"

using namespace Utility;

namespace Coursework2
{
  size_t BitStreamComparator::Compare(const BitStream & a, const BitStream & b)
  {
    size_t mismatches = 0;

    auto aIt = a.cbegin();
    auto bIt = b.cbegin();

    while (aIt != a.cend() && bIt != b.cend())
    {
      if (*(aIt++) != *(bIt++))
        mismatches++;
    }

    if (!(aIt == a.cend() && bIt == b.cend()))
      mismatches += std::max(a.size(), b.size()) - std::min(a.size(), b.size());
    
    return mismatches;
  }

  size_t BitStreamComparator::Compare(const std::string & aFilename, const std::string & bFilename)
  {
    BitStream a;
    BitStream b;

    BinaryFileIO::ReadFile(a, aFilename);
    BinaryFileIO::ReadFile(b, bFilename);

    return Compare(a, b);
  }

  bool BitStreamComparator::CompareMultiple(const std::vector<BitStream>& data)
  {
    for (auto it = data.cbegin() + 1; it != data.cend(); ++it)
    {
      if (Compare(data.front(), *it) > 0)
        return false;
    }

    return true;
  }

  bool BitStreamComparator::CompareMultiple(const std::vector<std::string> &filenames)
  {
    std::vector<BitStream> data;

    for (auto it = filenames.cbegin(); it != filenames.cend(); ++it)
    {
      BitStream s;
      BinaryFileIO::ReadFile(s, *it);
      data.push_back(s);
    }

    return CompareMultiple(data);
  }
}