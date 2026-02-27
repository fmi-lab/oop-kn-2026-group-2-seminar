#include "rational.hpp"

Rational::Rational(int numerator, int denominator) 
  : numerator(numerator), denominator(1) {
  set_denominator(denominator);
  int n = gcd();
  
  this->numerator /= n;
  this->denominator /= n;
}

int Rational::gcd() const {
  int a = std::min(numerator, denominator);
  int b = std::max(denominator, numerator);

  while (a != 0) {
    int temp = a;
    a = b % a;
    b = temp;
  }

  return b;
}

void Rational::set_numerator(int numerator) {
  this->numerator = numerator;
}

void Rational::set_denominator(int n) {
  if (n != 0) {
    denominator = n;
  }
}

int Rational::get_numerator() const {
  return numerator;
}

int Rational::get_denominator() const {
  return denominator;
}