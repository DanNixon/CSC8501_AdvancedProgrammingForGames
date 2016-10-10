#include <iostream>
#include <limits>

#define BS_GRID_DIMENSIONS 10
//#define DO_NOT_HIDE_SHIPS

#define SHIP_SUNK_FLAG std::numeric_limits<size_t>::max()

struct battleship_t
{
  char *name;
  size_t numSquares;
  size_t squaresRemaining;

  bool hasBeenSunk()
  {
    bool sunk = squaresRemaining == 0;
    if (sunk)
      squaresRemaining = SHIP_SUNK_FLAG;
    return sunk;
  }
};

struct grid_square_t
{
  size_t timesHit;
  battleship_t *ship;
};

size_t findSpace(const char *str);
void printStr(const char *str);
size_t strCopy(char *dest, size_t destLen, const char *src, size_t srcLen);

void printGridToStream(grid_square_t grid[][BS_GRID_DIMENSIONS],
                       std::ostream &str);
size_t shipSpacesRemaining(grid_square_t grid[][BS_GRID_DIMENSIONS]);
std::pair<size_t, size_t> getPositionFromStream(std::istream &str);
battleship_t *fireMissile(grid_square_t grid[][BS_GRID_DIMENSIONS],
                          std::pair<size_t, size_t> position);

int main(void)
{
  // Create ships
  battleship_t ships[2];
  ships[0] = {"Destroyer", 4, 4};
  ships[1] = {"Aircraft Carrier", 5, 5};

  // Create game grid
  grid_square_t grid[BS_GRID_DIMENSIONS][BS_GRID_DIMENSIONS];

  for (size_t y = 0; y < BS_GRID_DIMENSIONS; y++)
  {
    for (size_t x = 0; x < BS_GRID_DIMENSIONS; x++)
    {
      grid[y][x].timesHit = 0;
      grid[y][x].ship = nullptr;
    }
  }

  // Place ships
  // TODO: make this random
  for (size_t i = 0; i < ships[0].numSquares; i++)
    grid[4][i + 2].ship = &ships[0];
  for (size_t i = 0; i < ships[1].numSquares; i++)
    grid[6][i + 5].ship = &ships[1];

  printGridToStream(grid, std::cout);

  // Continue game while ships remain
  while (shipSpacesRemaining(grid) > 0)
  {
    // Get players next missile position
    std::cout << "Enter position \"x,y\":";
    auto position = getPositionFromStream(std::cin);

    // Check for ship hit
    battleship_t *hitShip = fireMissile(grid, position);
    if (hitShip)
    {
      std::cout << "Hit!\n";

      // Check for sunk ship
      if (hitShip->hasBeenSunk())
        std::cout << hitShip->name << " has been sunk!\n";
    }
    else
      std::cout << "Miss!\n";

    printGridToStream(grid, std::cout);
  }
  std::cout << "All ships sunk!\n";

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

void printGridToStream(grid_square_t grid[][BS_GRID_DIMENSIONS],
                       std::ostream &str)
{
  static const char DELIMITER = ' ';

  for (size_t y = 0; y < BS_GRID_DIMENSIONS; y++)
  {
    str << y << DELIMITER;
    for (size_t x = 0; x < BS_GRID_DIMENSIONS; x++)
    {
      battleship_t *ship = grid[y][x].ship;
      bool hit = grid[y][x].timesHit > 0;

      char c = '.';
      if (ship != nullptr)
      {
        if (hit)
          c = 'X';
#ifdef DO_NOT_HIDE_SHIPS
        else
          c = ship->name[0];
#endif
      }
      else
      {
        if (hit)
          c = '0';
      }
      str << c << DELIMITER;
    }
    str << '\n';
  }

  str << DELIMITER << DELIMITER;
  for (size_t x = 0; x < BS_GRID_DIMENSIONS; x++)
    str << x << DELIMITER;
  str << '\n';
}

size_t shipSpacesRemaining(grid_square_t grid[][BS_GRID_DIMENSIONS])
{
  size_t n = 0;

  for (size_t y = 0; y < BS_GRID_DIMENSIONS; y++)
    for (size_t x = 0; x < BS_GRID_DIMENSIONS; x++)
      if (grid[y][x].ship != nullptr && grid[y][x].timesHit == 0)
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

battleship_t *fireMissile(grid_square_t grid[][BS_GRID_DIMENSIONS],
                          std::pair<size_t, size_t> position)
{
  grid_square_t *square = &(grid[position.second][position.first]);
  bool hasShip = square->ship != nullptr;
  square->timesHit++;
  if (hasShip)
    square->ship->squaresRemaining--;
  return hasShip && square->timesHit == 1 ? square->ship : nullptr;
}
