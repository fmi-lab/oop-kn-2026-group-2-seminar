#include <iostream>

#include "rational.hpp"
#include "temp.hpp"

int main() {
  Rational r(2, 4);

  std::cout << r.get_numerator() << '/' << r.get_denominator() << '\n';
  return 0;
}