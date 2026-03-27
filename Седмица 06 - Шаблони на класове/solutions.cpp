#include <iostream>
#include "sorted.hpp"

int main() {
  int arr[] = {5, 1, 8, 4, 11};
  Sorted<int> s(arr, 5);
  s.add(6);

  s.filter([](const int& element){
    return element % 2 == 0;
  });

  std::cout << s << '\n';
  return 0;
}