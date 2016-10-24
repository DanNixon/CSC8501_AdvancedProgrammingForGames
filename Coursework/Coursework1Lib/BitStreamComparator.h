/** @file */

#pragma once

#include <vector>

namespace Coursework1
{
class BitStreamComparator
{
public:
  typedef std::vector<bool> BitStream;
  typedef std::vector<std::vector<size_t>> IndexListList;

public:
  static size_t Compare(const BitStream &a, const BitStream &b);
  static size_t Compare(const std::string &aFilename, const std::string &bFilename);

  static bool CompareMultiple(const std::vector<BitStream> &data);
  static bool CompareMultiple(const std::vector<std::string> &filenames);

  static void FindSimilar(IndexListList &results, const std::vector<BitStream> &data);
  static void FindSimilar(IndexListList &results, const std::vector<std::string> &filenames);

private:
  static void LoadData(std::vector<BitStream>& data, const std::vector<std::string> &filenames);
};
}