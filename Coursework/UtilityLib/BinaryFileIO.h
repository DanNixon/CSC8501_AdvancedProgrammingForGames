/** @file */

#pragma once

#include <iostream>
#include <vector>

namespace Utility
{
class BinaryFileIO
{
public:
  static size_t Read(std::vector<bool> &bits, std::istream &in);
  static size_t Write(const std::vector<bool> &bits, std::ostream &out);

  static size_t ReadFile(std::vector<bool> &bits, const std::string &filename);
  static size_t WriteFile(const std::vector<bool> &bits, const std::string &filename);
};
}