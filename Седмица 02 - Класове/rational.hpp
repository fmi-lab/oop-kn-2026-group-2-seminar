#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <algorithm>

class Rational {
public:
  Rational(int numer, int denom = 1);

  void set_numerator(int n);
  void set_denominator(int n);
  int get_numerator() const;
  int get_denominator() const;

private:
  int numerator;
  int denominator;

  int gcd() const;
};

#endif