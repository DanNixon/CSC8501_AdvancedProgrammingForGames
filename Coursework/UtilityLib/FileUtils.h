/** @file */

#pragma once

#include <vector>

namespace Utility
{
/**
 * @class FileUtils
 * @author Dan Nixon
 * @brief Provides functions for working with files on disk.
 */
class FileUtils
{
public:
  static void FindFiles(std::vector<std::string> &filenames, const std::string &directory,
                        const std::string &glob);
};
}
