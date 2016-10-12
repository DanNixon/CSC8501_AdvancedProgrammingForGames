#include "MatrixInt.h"

MatrixInt::MatrixInt(int x, int y)
  : x_size(x)
  , y_size(y)
{
  cells = new int *[x_size];
  for (int i = 0; i < x_size; ++i)
  {
    cells[i] = new int[y_size];
  }
}

MatrixInt::~MatrixInt()
{
  for (int i = 0; i < x_size; ++i)
  {
    delete[] cells[i];
  }
  delete[] cells;
}

int MatrixInt::get_element(int x, int y) const
{
  return (cells[x][y]);
}

void MatrixInt::set_element(int x, int y, int elem)
{
  cells[x][y] = elem;
}