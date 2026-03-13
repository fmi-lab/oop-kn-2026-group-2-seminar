#include <algorithm>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <type_traits>

class Polynomial {
public:
  Polynomial() 
    : coefficients(nullptr), size(0), capacity(0) {}

  Polynomial(const Polynomial& other)
    : coefficients(new float[other.capacity]),
      size(other.size),
      capacity(other.capacity) {
    for (std::size_t i = 0; i < other.size; ++i) {
      coefficients[i] = other.coefficients[i];
    }
  }

  ~Polynomial() {
    delete [] coefficients;
  }

  Polynomial& operator=(const Polynomial& other) {
    Polynomial copy(other);
    swap(copy);

    return *this;
  }

  Polynomial& add_coefficient(float c) {
    if (size == capacity) {
      resize();
    }

    coefficients[size++] = c;

    return *this;
  }

  float operator()(float x) const {
    float result = 0;
    
    for (std::size_t i = 0; i < size; ++i) {
      result += std::pow(x, i) * coefficients[i];  
    }

    return result;
  }

  float operator[](std::size_t index) const {
    return coefficients[index];
  }

  // float& operator[](std::size_t index) {
  //   return coefficients[index];
  // }

  Polynomial operator+(const Polynomial& other) const {
    Polynomial result;
    std::size_t min_size = std::min(size, other.size);

    for (std::size_t i = 0; i < min_size; ++i) {
      result.add_coefficient(coefficients[i] + other.coefficients[i]);
    }
    
    const Polynomial& larger = size != min_size ? *this : other;
    for (std::size_t i = min_size; i < larger.size; ++i) {
      result.add_coefficient(larger[i]);
    }

    return result;
  }

  Polynomial& operator+=(const Polynomial& other) {
    std::size_t min_size = std::min(size, other.size);

    for (std::size_t i = 0; i < min_size; ++i) {
      coefficients[i] += other.coefficients[i];
    }

    if (size == min_size) {
      for (std::size_t i = size; i < other.size; ++i) {
        add_coefficient(other.coefficients[i]);
      }
    }

    return *this;
  }

  bool operator==(const Polynomial& other) const {
    // TODO
  }

  friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    for (int i = poly.size - 1; i >= 1; --i) {
      os << poly[i] << "x^" << i << " + ";
    }

    return os << poly[0];
  }

private:
  float* coefficients;
  std::size_t size, capacity;

  void swap(Polynomial& other) {
    std::swap(coefficients, other.coefficients);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
  }

  void resize() {
    if (capacity == 0) {
      capacity = 1;
    }

    float* new_coefficients = new float[capacity *= 2];
    for (std::size_t i = 0; i < size; ++i) {
      new_coefficients[i] = coefficients[i];
    }

    delete [] coefficients;
    coefficients = new_coefficients;
  }
};

int main() {
  Polynomial poly;
  poly.add_coefficient(2).add_coefficient(3).add_coefficient(1);

  std::cout << poly << '\n';
  std::cout << poly(2) << '\n';

  Polynomial p3;
  p3
    .add_coefficient(4)
    .add_coefficient(3)
    .add_coefficient(3)
    .add_coefficient(4);

  poly += p3;

  std::cout << poly << '\n';

  return 0;
}