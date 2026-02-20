#include <iostream>

template <typename T, typename U>
using UnaryOperation = U(*)(T);

template <typename T, typename U, typename S>
using BinaryOperation = S(*)(T, U);

template <typename T>
bool is_fixed_point(UnaryOperation<T, T> f, T x) {
  return f(x) == x;
}

template <typename T, typename U, typename S>
auto composition(UnaryOperation<T, U> f, UnaryOperation<U, S> g) {
  return [f, g](T x){
    return g(f(x));
  };
}

auto derivative(UnaryOperation<double, double> f) {
  constexpr double h = 1e-6;
  return [f, h](double x){
    return (f(x + h) - f(x)) / h;
  };
}

template <typename T>
void print(T* begin, T* end) {
  while (begin != end) {
    std::cout << *begin << ' ';
    ++begin;
  }
  std::cout << '\n';
}

template <typename T>
void map(T* begin, T* end, UnaryOperation<T, T> f) {
  while (begin != end) {
    *begin = f(*begin);
    ++begin;
  }
}

template <typename T, typename U>
U reduce(BinaryOperation<T, U, U> op, U e, T* begin, T* end) {
  while (begin != end) {
    e = op(*begin++, e);
  }

  return e;
}

int sum_odd_squares(int* begin, int* end) {
  return reduce<int, int>([](int current, int result){
    if (current % 2 == 1) {
      return current * current + result;
    }

    return result;
  }, 0, begin, end);
}

int main() {
  int arr[] = {1, 2 ,3 , 4, 5, 6, 7, 8, 9, 10};
  std::cout << sum_odd_squares(std::begin(arr), std::end(arr)) << '\n'; // -> 165
  return 0;
}