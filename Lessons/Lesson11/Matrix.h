#pragma once

template <typename T, size_t X, size_t Y> class Matrix
{
public:
  Matrix();
  Matrix(const Matrix<T, X, Y> &other);
  ~Matrix();

  inline int get_x_size() const
  {
    return X;
  }

  inline int get_y_size() const
  {
    return Y;
  }

  T get_element(int x, int y) const;
  void set_element(int x, int y, T elem);

protected:
  T **cells;
};

template <typename T, size_t X, size_t Y> Matrix<T, X, Y>::Matrix()
{
  cells = new T *[X];
  for (size_t i = 0; i < X; ++i)
    cells[i] = new T[Y];
}

template <typename T, size_t X, size_t Y> Matrix<T, X, Y>::Matrix(const Matrix<T, X, Y> &other)
{
  cells = new T *[X];
  for (size_t x = 0; x < X; ++x)
  {
    cells[x] = new T[Y];
    for (size_t y = 0; y < Y; y++)
      cells[x][y] = other.cells[x][y];
  }
}

template <typename T, size_t X, size_t Y> Matrix<T, X, Y>::~Matrix()
{
  for (int i = 0; i < X; ++i)
    delete[] cells[i];
  delete[] cells;
}

template <typename T, size_t X, size_t Y>
T Matrix<T, X, Y>::get_element(int x, int y) const
{
  return (cells[x][y]);
}

template <typename T, size_t X, size_t Y>
void Matrix<T, X, Y>::set_element(int x, int y, T elem)
{
  cells[x][y] = elem;
}
