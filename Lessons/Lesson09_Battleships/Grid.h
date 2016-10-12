#pragma once

#include "GridSquare.h"

template<size_t W, size_t H>
class Grid
{
public:
  Grid()
  {
  }

  ~Grid()
  {
  }

  inline size_t width() const
  {
    return W;
  }

  inline size_t height() const
  {
    return H;
  }

  inline void hit(size_t x, size_t y)
  {
    m_grid[x][y]->hit();
  }
  
private:
  GridSquare *m_grid[W][H];
};