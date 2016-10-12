#pragma once

#include <string>

class Battleship
{
public:
  Battleship(const std::string &name, size_t size);
  virtual ~Battleship();

  inline std::string name() const
  {
    return m_name;
  }

  inline size_t squares() const
  {
    return m_squares;
  }

  inline size_t uniqueHits() const
  {
    return m_uniqueHits;
  }

  inline size_t squaresRemaining() const
  {
    return m_squares - m_uniqueHits;
  }

private:
  const std::string m_name;
  const size_t m_squares;
  size_t m_uniqueHits;
};