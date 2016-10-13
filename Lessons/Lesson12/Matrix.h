#pragma once

template <typename T, size_t X, size_t Y> class Matrix
{
public:
  Matrix();
  Matrix(const Matrix<T, X, Y> &src);
  ~Matrix();

  Matrix<T, X, Y> &operator=(const Matrix<T, X, Y> &rhs);

  template <typename E>
  friend std::ostream &operator<<(std::ostream &ostr,
                                  const Matrix<E, X, Y> &mtx);

  template <typename E>
  friend Matrix<E, X, Y> operator*(const Matrix<E, X, Y> &a,
                                   const Matrix<E, X, Y> &b);

  inline size_t get_x_size() const
  {
    return X;
  }

  inline size_t get_y_size() const
  {
    return Y;
  }

  T get_element(size_t x, size_t y) const;
  T &get_element(size_t x, size_t y);
  void set_element(size_t x, size_t y, T elem);

protected:
  T *m_data;
  size_t m_length;
};

template <typename T, size_t X, size_t Y>
Matrix<T, X, Y>::Matrix()
    : m_length(X * Y)
{
  m_data = new T[m_length];
  memset(m_data, 0, m_length * sizeof(T));
}

template <typename T, size_t X, size_t Y>
Matrix<T, X, Y>::Matrix(const Matrix<T, X, Y> &src)
    : m_length(X * Y)
{
  m_data = new T[m_length];
  memcpy_s(m_data, m_length * sizeof(T), src.m_data, m_length * sizeof(T));
}

template <typename T, size_t X, size_t Y> Matrix<T, X, Y>::~Matrix()
{
  delete[] m_data;
}

template <typename T, size_t X, size_t Y>
Matrix<T, X, Y> &Matrix<T, X, Y>::operator=(const Matrix<T, X, Y> &rhs)
{
  if (this == &rhs)
    return (*this);

  // Release old memory
  delete[] m_data;

  // Copy new values
  m_length = rhs.m_length;
  m_data = new T[m_length];
  memcpy_s(m_data, m_length * sizeof(T), rhs.m_data, m_length * sizeof(T));

  return *this;
}

template <typename E, size_t X, size_t Y>
std::ostream &operator<<(std::ostream &ostr, const Matrix<E, X, Y> &mtx)
{
  for (int x = 0; x < X; ++x)
  {
    for (int y = 0; y < Y; ++y)
      ostr << mtx.get_element(x, y) << ", ";

    ostr << '\n';
  }
  ostr << '\n';

  return ostr;
}

template <typename E, size_t X, size_t Y>
Matrix<E, X, Y> operator*(const Matrix<E, X, Y> &a, const Matrix<E, X, Y> &b)
{
  Matrix<E, X, Y> result;

  for (size_t x = 0; x < X; ++x)
  {
    for (size_t y = 0; y < Y; ++y)
    {
      for (size_t xx = 0; xx < X; ++xx)
      {
        result.get_element(x, y) += a.get_element(y, xx) * b.get_element(x, xx);
      }
    }
  }

  return result;
}

template <typename T, size_t X, size_t Y>
T Matrix<T, X, Y>::get_element(size_t x, size_t y) const
{
  return m_data[x * Y + y];
}

template <typename T, size_t X, size_t Y>
T &Matrix<T, X, Y>::get_element(size_t x, size_t y)
{
  return m_data[x * Y + y];
}

template <typename T, size_t X, size_t Y>
void Matrix<T, X, Y>::set_element(size_t x, size_t y, T elem)
{
  size_t i = (x * Y) + y;
  m_data[i] = elem;
}
