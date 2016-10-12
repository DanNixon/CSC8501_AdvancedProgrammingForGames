#pragma once

class MatrixInt
{
public:
  MatrixInt(int x = default_x, int y = default_y);
  ~MatrixInt();

  inline int get_x_size() const
  {
    return x_size;
  }

  inline int get_y_size() const
  {
    return y_size;
  }

  int get_element(int x, int y) const;
  void set_element(int x, int y, int elem);
  
  static const int default_x = 3;
  static const int default_y = 3;

protected:
  int **cells;
  int x_size;
  int y_size;
};