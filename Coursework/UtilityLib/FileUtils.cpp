/** @file */

#include "FileUtils.h"

#include <windows.h>

// Based on: http://stackoverflow.com/a/20847429

namespace Utility
{
void FileUtils::FindFiles(std::vector<std::string> &filenames, const std::string &searchPath)
{
  WIN32_FIND_DATA fd;
  HANDLE hFind = ::FindFirstFile(searchPath.c_str(), &fd);
  if (hFind != INVALID_HANDLE_VALUE)
  {
    do
    {
      if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
      {
        filenames.push_back(fd.cFileName);
      }
    } while (::FindNextFile(hFind, &fd));
    ::FindClose(hFind);
  }
}
}