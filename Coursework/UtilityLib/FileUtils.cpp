/** @file */

#include "FileUtils.h"

#include <windows.h>

namespace Utility
{
/**
 * @brief Finds files in a given directory that match a given glob.
 * @param filenames Reference to vector to store output in
 * @param directory Directory to search in (must have training slash)
 * @param glob Glob to find files by (use * to find all files)
 *
 * Based on: http://stackoverflow.com/a/20847429
 */
void FileUtils::FindFiles(std::vector<std::string> &filenames, const std::string &directory,
                          const std::string &glob)
{
  WIN32_FIND_DATA fd;
  HANDLE hFind = ::FindFirstFile((directory + glob).c_str(), &fd);
  if (hFind != INVALID_HANDLE_VALUE)
  {
    do
    {
      if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        filenames.push_back(directory + fd.cFileName);
    } while (::FindNextFile(hFind, &fd));
    ::FindClose(hFind);
  }
}
}
