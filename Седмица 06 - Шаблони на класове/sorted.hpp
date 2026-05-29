#ifndef SORTED_HPP
#define SORTED_HPP

#include <cstddef>
#include <functional>
#include <ostream>
#include <utility>

template <typename T>
class Sorted {
public:
  Sorted();
  Sorted(T arr[], std::size_t size);

  Sorted(const Sorted& other);
  ~Sorted();
  Sorted<T> operator=(const Sorted& other);
  Sorted(Sorted<T>&& other);
  Sorted<T>& operator=(Sorted<T>&& other);

  Sorted<T>& add(const T& element);
  const T& operator[](std::size_t index) const;
  std::size_t length() const {
    return size;
  }

  Sorted<T>& filter(const std::function<bool(const T&)>& predicate);

  // template <typename U>
  // friend std::ostream& operator<<(std::ostream& os, const Sorted<U>& s);

private:
  T* data;
  std::size_t size, capacity;

  void swap(Sorted& other);
  void resize();
  void insert(const T& element);

  void shift(std::size_t index);
};

template <typename T>
Sorted<T>::Sorted() : data(nullptr), size(0), capacity(0) {}

template <typename T>
Sorted<T>::Sorted(const Sorted& other)
  : data(new T[other.capacity]),
    size(other.size),
    capacity(other.capacity) {
  for (std::size_t i = 0; i < other.size; ++i) {
    data[i] = other.data[i];
  }
}

template <typename T>
Sorted<T>::~Sorted() {
  delete [] data;
}

template <typename T>
Sorted<T> Sorted<T>::operator=(const Sorted& other) {
  Sorted<T> copy(other);
  swap(copy);

  return *this;
}

template <typename T>
Sorted<T>& Sorted<T>::add(const T& element) {
  if (size == capacity) {
    resize();
  }

  insert(element);
  return *this;
}

template <typename T>
void Sorted<T>::swap(Sorted& other) {
  std::swap(data, other.data);
  std::swap(size, other.size);
  std::swap(capacity, other.capacity);
}

template <typename T>
void Sorted<T>::resize() {
  if (capacity == 0) {
    capacity = 1;
  }

  T* new_data = new T[capacity *= 2];
  for (std::size_t i = 0; i < size; ++i) {
    new_data[i] = data[i];
  }

  delete [] data;
  data = new_data;
}

template <typename T>
void Sorted<T>::insert(const T& element) {
  data[size] = element;

  int i = size;
  while (i >= 1 && data[i - 1] > data[i]) {
    std::swap(data[i - 1], data[i]);
    --i;
  }

  ++size;
} 

// template <typename U>
// std::ostream& operator<<(std::ostream& os, const Sorted<U>& s) {
//   for (std::size_t i = 0; i < s.size; ++i) {
//     os << s.data[i] << ' ';
//   }

//   return os;
// }

template <typename T>
std::ostream& operator<<(std::ostream& os, const Sorted<T>& s) {
  for (std::size_t i = 0; i < s.length(); ++i) {
    os << s[i] << ' ';
  }

  return os;
}

template <typename T>
const T& Sorted<T>::operator[](std::size_t index) const {
  return data[index];
}

template <typename T>
Sorted<T>::Sorted(T arr[], std::size_t size)
  : data(new T[size]),
    size(0),
    capacity(size) {
  for (std::size_t i = 0; i < size; ++i) {
    insert(arr[i]);
  }
}

template <typename T>
Sorted<T>& Sorted<T>::filter(const std::function<bool(const T&)>& predicate) {
  int i = 0;
  while (i < size) {
    if (!predicate(data[i])) {
      shift(i);
      --size;
    } else {
      ++i;
    }
  }

  return *this;
}

template <typename T>
void Sorted<T>::shift(std::size_t index) {
  for (std::size_t i = index + 1; i < size; ++i) {
    std::swap(data[i - 1], data[i]);
  }
}


template <typename T>
Sorted<T>::Sorted(Sorted<T>&& other) 
  : data(std::exchange(other.data, nullptr)),
    size(std::move(other.size)),
    capacity(std::move(other.capacity)) {}

template <typename T>
Sorted<T>& Sorted<T>::operator=(Sorted<T>&& other) {
  Sorted<T> copy(std::move(other));
  swap(copy);

  return *this;
}

#endif