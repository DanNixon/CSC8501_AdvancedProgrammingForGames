/** @file */

#pragma once

#include <vector>

#include "CircuitSimulatorLib/BitStream.h"

namespace Coursework
{
/**
 * @class BitStreamComparator
 * @author Dan Nixon
 * @brief Used to make comparisons between streams of binary data.
 */
class BitStreamComparator
{
public:
  /**
   * @brief A list of list of indices.
   */
  typedef std::vector<std::vector<size_t>> IndexListList;

public:
  static size_t Compare(const CircuitSimulator::BitStream &a, const CircuitSimulator::BitStream &b);
  static size_t Compare(const std::string &aFilename, const std::string &bFilename);

  static bool CompareMultiple(const std::vector<CircuitSimulator::BitStream> &data);
  static bool CompareMultiple(const std::vector<std::string> &filenames);

  static void FindSimilar(IndexListList &results,
                          const std::vector<CircuitSimulator::BitStream> &data);
  static void FindSimilar(IndexListList &results, const std::vector<std::string> &filenames);

private:
  static void LoadData(std::vector<CircuitSimulator::BitStream> &data,
                       const std::vector<std::string> &filenames);
};
}
