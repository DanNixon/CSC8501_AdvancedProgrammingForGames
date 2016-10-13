#pragma once

class Battleship;

class GridSquare
{
public:
  GridSquare(Battleship *ship = nullptr);
  virtual ~GridSquare();

  void hit();

private:
  Battleship *m_ship;
  size_t m_timesHit;
};