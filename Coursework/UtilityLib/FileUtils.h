/** @file */

#pragma once

#include <vector>

namespace Utility
{
class FileUtils
{
public:
  static void FindFiles(std::vector<std::string> &filenames, const std::string &searchPath);
};
}