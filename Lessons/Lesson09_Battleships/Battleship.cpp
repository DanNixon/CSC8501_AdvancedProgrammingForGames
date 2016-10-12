#include "Battleship.h"

Battleship::Battleship(const std::string &name, size_t size)
  : m_name(name), m_squares(size)
{
}

Battleship::~Battleship()
{
}