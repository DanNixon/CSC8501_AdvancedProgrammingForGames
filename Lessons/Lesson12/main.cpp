#include <iostream>

#include "Matrix.h"

int main()
{
  Matrix<int, 3, 3> mtx1;
  mtx1.set_element(0, 0, 1);
  mtx1.set_element(1, 1, 4);
  mtx1.set_element(2, 2, 6);
  std::cout << "matrix 1:\n" << mtx1;

  Matrix<int, 3, 3> mtx2;
  mtx2.set_element(0, 0, 1);
  mtx2.set_element(1, 1, 4);
  mtx2.set_element(2, 2, 2);
  std::cout << "matrix 2:\n" << mtx2;

  Matrix<int, 3, 3> mtx3;
  mtx3 = mtx2;
  std::cout << "matrix 3 assigned from matrix 2:\n" << mtx3;

  Matrix<int, 3, 3> product = (mtx1 * mtx3);
  std::cout << "matrix product assigned from mtx1 * mtx3:\n" << product;

  return 0;
}
