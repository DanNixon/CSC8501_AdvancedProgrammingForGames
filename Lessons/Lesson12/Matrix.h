#pragma once

template <typename T> class Matrix
{
public:
  static const size_t DEFAULT_X = 3;
  static const size_t DEFAULT_Y = 3;

public:
  Matrix(size_t x = DEFAULT_X, size_t y = DEFAULT_Y);
  Matrix(const Matrix<T> &src);
  ~Matrix();

  Matrix<T> &operator=(const Matrix<T> &rhs);

  template <typename E>
  friend std::ostream &operator<<(std::ostream &ostr, const Matrix<E> &mtx);

  template <typename E>
  friend Matrix<E> operator*(const Matrix<E> &a, const Matrix<E> &b);

  inline size_t get_x_size() const
  {
    return m_xSize;
  }

  inline size_t get_y_size() const
  {
    return m_ySize;
  }

  T get_element(int x, int y) const;
  void set_element(int x, int y, T elem);

protected:
  T *m_data;
  size_t m_xSize;
  size_t m_ySize;
  size_t m_length;
};

template <typename T>
Matrix<T>::Matrix(size_t x, size_t y)
    : m_xSize(x)
    , m_ySize(y)
    , m_length(x * y)
{
  m_data = new T[m_length];
  memset(m_data, 0, m_length * sizeof(T));
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T> &src)
    : m_xSize(src.m_xSize)
    , m_ySize(src.m_ySize)
    , m_length(src.m_xSize * src.m_ySize)
{
  m_data = new T[m_length];
  memcpy_s(m_data, m_length * sizeof(T), src.m_data, m_length * sizeof(T));
}

template <typename T> Matrix<T>::~Matrix()
{
  delete[] m_data;
}

template <typename T> Matrix<T> &Matrix<T>::operator=(const Matrix<T> &rhs)
{
  if (this == &rhs)
    return (*this);

  // Release old memory
  delete[] m_data;

  // Copy new values
  m_xSize = rhs.m_xSize;
  m_ySize = rhs.m_ySize;
  m_length = rhs.m_length;

  m_data = new T[m_length];
  memcpy_s(m_data, m_length * sizeof(T), rhs.m_data, m_length * sizeof(T));

  return *this;
}

template <typename E>
std::ostream &operator<<(std::ostream &ostr, const Matrix<E> &mtx)
{
  for (int x = 0; x < mtx.m_xSize; ++x)
  {
    for (int y = 0; y < mtx.m_ySize; ++y)
      ostr << mtx.m_data[x * mtx.m_ySize + y] << ", ";

    ostr << '\n';
  }
  ostr << '\n';

  return ostr;
}

template <typename E>
Matrix<E> operator*(const Matrix<E> &a, const Matrix<E> &b)
{
  Matrix<E> result(a.m_xSize, b.m_ySize);

  for (size_t x = 0; x < a.m_xSize; ++x)
  {
    for (size_t y = 0; y < a.m_xSize; ++y)
    {
      for (size_t xx = 0; xx < a.m_xSize; ++xx)
      {
        result.m_data[x * a.m_ySize + y] +=
            a.m_data[y * a.m_ySize + xx] * b.m_data[x * a.m_ySize + xx];
      }
    }
  }

  return result;
}

template <typename T> T Matrix<T>::get_element(int x, int y) const
{
  return m_data[x * m_ySize + y];
}

template <typename T> void Matrix<T>::set_element(int x, int y, T elem)
{
  m_data[x * m_ySize + y] = elem;
}
