#include <iostream>

#include "Matrix.h"
#include "MatrixInt.h"

int main()
{
  MatrixInt m(3, 4);
  m.set_element(2, 2, 8);
  std::cout << "element at 2,2 is " << m.get_element(2, 2) << '\n';

  Matrix<int, 3, 3> intM;
  intM.set_element(1, 1, 4);
  std::cout << "element at 1,1 is " << intM.get_element(1, 1) << '\n';

  Matrix<double, 3, 3> doubM;
  std::cout << "Dims: x=" << doubM.get_x_size() << ", y=" << doubM.get_y_size() << '\n';
  doubM.set_element(2, 2, 8.421);
  std::cout << "element at 2,2 is " << doubM.get_element(2, 2) << '\n';

  Matrix<double, 3, 3> doubM2(doubM);
  std::cout << "element at 2,2 is " << doubM2.get_element(2, 2) << '\n';

  return 0;
}