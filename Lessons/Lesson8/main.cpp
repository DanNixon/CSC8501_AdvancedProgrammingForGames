#include <iostream>

#define BS_GRID_DIMENSIONS 10

enum battleship_t
{
  BS_AIRCRAFTCARRIER = 5,
  BS_DESTROYER = 4,

  BS_NONE = -1,
  BS_HIT = -2,
  BS_MISS = -3
};

size_t findSpace(const char *str);
void printStr(const char *str);
size_t strCopy(char *dest, size_t destLen, const char *src, size_t srcLen);

void printGridToStream(battleship_t grid[][BS_GRID_DIMENSIONS],
                       std::ostream &str);
size_t shipSpacesRemaining(battleship_t grid[][BS_GRID_DIMENSIONS]);
std::pair<size_t, size_t> getPositionFromStream(std::istream &str);
bool fireMissile(battleship_t grid[][BS_GRID_DIMENSIONS],
                 std::pair<size_t, size_t> position);

int main(void)
{
  // Create game grid
  battleship_t grid[BS_GRID_DIMENSIONS][BS_GRID_DIMENSIONS];

  for (size_t y = 0; y < BS_GRID_DIMENSIONS; y++)
    for (size_t x = 0; x < BS_GRID_DIMENSIONS; x++)
      grid[y][x] = BS_NONE;

  // Place ships
  for (size_t i = 0; i < (size_t)BS_AIRCRAFTCARRIER; i++)
    grid[4][i + 2] = BS_AIRCRAFTCARRIER;
  for (size_t i = 0; i < (size_t)BS_DESTROYER; i++)
    grid[6][i + 5] = BS_DESTROYER;

  printGridToStream(grid, std::cout);

  while (shipSpacesRemaining(grid) > 0)
  {
    std::cout << "Enter position \"x,y\":";
    auto position = getPositionFromStream(std::cin);

    if (fireMissile(grid, position))
      std::cout << "Hit!\n";
    else
      std::cout << "Miss!\n";

    printGridToStream(grid, std::cout);
  }

#if 0
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
#endif

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

void printGridToStream(battleship_t grid[][BS_GRID_DIMENSIONS],
                       std::ostream &str)
{
  for (size_t y = 0; y < BS_GRID_DIMENSIONS; y++)
  {
    for (size_t x = 0; x < BS_GRID_DIMENSIONS; x++)
    {
      char c;
      switch (grid[y][x])
      {
      case BS_AIRCRAFTCARRIER:
        c = 'A';
        break;
      case BS_DESTROYER:
        c = 'D';
        break;
      case BS_HIT:
        c = 'x';
        break;
      case BS_MISS:
        c = '0';
        break;
      case BS_NONE:
        c = '-';
        break;
      default:
        c = ' ';
      }
      str << c << ' ';
    }
    str << '\n';
  }
}

size_t shipSpacesRemaining(battleship_t grid[][BS_GRID_DIMENSIONS])
{
  size_t n = 0;

  for (size_t y = 0; y < BS_GRID_DIMENSIONS; y++)
    for (size_t x = 0; x < BS_GRID_DIMENSIONS; x++)
      if (grid[y][x] > 0)
        n++;

  return n;
}

std::pair<size_t, size_t> getPositionFromStream(std::istream &str)
{
  size_t x, y;
  char c;

  str >> x >> c >> y;

  return std::make_pair(x, y);
}

bool fireMissile(battleship_t grid[][BS_GRID_DIMENSIONS],
                 std::pair<size_t, size_t> position)
{
  battleship_t *square = &(grid[position.second][position.first]);
  if (*square > 0)
  {
    *square = BS_HIT;
    return true;
  }
  else
  {
    *square = BS_MISS;
    return false;
  }
}
