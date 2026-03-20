#include <complex>
#include <cstddef>
#include <cstring>
#include <ios>
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <utility>

constexpr std::size_t MAX_SIZE = 256;

namespace Math {
  constexpr float EPSILON = 1e-6;

  bool float_equal(float f1, float f2) {
    return std::fabs(f1 - f2) < EPSILON;    
  }
}

class String;

class Dish {
public:
  Dish(const char* name = "", float price = 0.0, unsigned quantity = 0, unsigned calories = 0)
    : name(new char[strlen(name) + 1]{}),
      price(price),
      quantity(quantity),
      calories(calories) {
    strcpy(this->name, name);
  }

  Dish(const Dish& other)
    : name(new char[strlen(other.name) + 1]{}),
      price(other.price),
      quantity(other.quantity),
      calories(other.calories) {
    strcpy(name, other.name);
  }

  ~Dish() {
    delete [] name;
  }

  Dish& operator=(const Dish& other) {
    Dish copy(other);
    swap(copy);

    return *this;
  }

  bool operator<(const Dish& other) const {
    float this_ratio = price / quantity;
    float other_ratio = other.price / other.quantity;

    if (Math::float_equal(this_ratio, other_ratio)) {
      return calories < other.calories;
    }

    return this_ratio < other_ratio;
  }

  friend std::ostream& operator<<(std::ostream& os, const Dish& dish) {
    return os << "Name: " << dish.name << '\n'
              << "Price: " << dish.price << '\n'
              << "Quantity: " << dish.quantity << '\n'
              << "Calories: " << dish.calories;
  }

private:
  char* name;
  float price;
  unsigned quantity, calories;

  void swap(Dish& other) {
    using std::swap;

    swap(name, other.name);
    swap(price, other.price);
    swap(quantity, other.quantity);
    swap(calories, other.calories);
  }
};

std::istream& operator>>(std::istream& is, Dish& dish) {
  char name[MAX_SIZE]{};
  float price;
  unsigned quantity, calories;

  is.getline(name, MAX_SIZE);
  is >> price >> quantity >> calories;
  is.ignore();

  dish = Dish(name, price, quantity, calories);

  return is;
}

enum class KitchenPosition {
  KitchenPorter,
  JuniorChef,
  HeadChef
};

class Cook {
public:
  Cook(const char* name, KitchenPosition position) 
    : // TODO: other...
      dishes(nullptr), size(0), capacity(0) {}

private:
  char* name;
  KitchenPosition position;

  struct DishEntry {
    Dish dish;
    unsigned minutes;
  };

  DishEntry* dishes;
  std::size_t size, capacity;
};

int main() {
  Dish dish, dish2;
  std::cin >> dish >> dish2;

  std::cout << dish << '\n' << dish2 << '\n';
  std::cout << std::boolalpha << (dish < dish2) << '\n';
  return 0;
}