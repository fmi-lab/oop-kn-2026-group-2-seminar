#include <iostream>
#include <utility>
#include <vector>
#include "../Седмица 07 - Автоматизирани тестове/car.hpp"

template <typename T>
class UniquePointer {
public:
  UniquePointer(T* data) : data(data) {}

  UniquePointer(const UniquePointer& other) = delete;
  UniquePointer<T>& operator=(const UniquePointer& other) = delete;

  ~UniquePointer() {
    delete data;
  }

  UniquePointer(UniquePointer&& other)
    : data(std::exchange(other.data, nullptr)) {}

  UniquePointer<T>& operator=(UniquePointer& other) {
    UniquePointer<T> copy(std::move(other));
    std::swap(data, other.data);

    return *this;
  }

  T& operator*() {
    return *data;
  }

  const T& operator*() const {
    return *data;
  }
  
  T* operator->() {
    return data;
  }

private:
  T* data;
};

template <typename T>
class A {
public:
  A(UniquePointer<T>&& data) : data(std::move(data)) {}

  UniquePointer<T>& operator->() {
    return data;
  }
private:
  UniquePointer<T> data;
};

int main() {
  UniquePointer<Car> car = new Car("Toyota", "Camry", 200);

  car->get_model();
  A<Car> a(std::move(car));
  a->get_model();

  std::vector<UniquePointer<Car>> arr;

  return 0;
}