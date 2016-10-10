#include <iostream>

size_t findSpace(const char *str);
void printStr(const char *str);
size_t strCopy(char *dest, size_t destLen, const char *src, size_t srcLen);

int main(void)
{
  char *name = "Dan Nixon";
  size_t spaceIdx = findSpace(name);
  std::cout << "name = ";
  printStr(name);

  size_t firstLen = spaceIdx + 1;
  size_t lastLen = strlen(name) - spaceIdx;

  char *first = new char[firstLen];
  strCopy(first, firstLen, name, spaceIdx);

  char *last = new char[lastLen];
  strCopy(last, lastLen, name + spaceIdx + 1, strlen(name) - spaceIdx);

  std::cout << "first = ";
  printStr(first);
  std::cout << "last = ";
  printStr(last);

  return 0;
}

size_t findSpace(const char *str)
{
  size_t i;
  for (i = 0; i < strlen(str); i++)
  {
    if (str[i] == ' ')
      break;
  }
  return i;
}

void printStr(const char *str)
{
  std::cout << '\"';
  for (size_t i = 0; i < strlen(str); i++)
    std::cout << str[i];
  std::cout << "\"\n";
}

size_t strCopy(char *dest, size_t destLen, const char *src, size_t srcLen)
{
  char *destEnd = dest + destLen - 1;
  const char *srcEnd = src + srcLen;

  size_t i = 0;
  while (dest != destEnd && src != srcEnd)
  {
    *(dest++) = *(src++);
    i++;
  }
  *dest = '\0';

  return i;
}
