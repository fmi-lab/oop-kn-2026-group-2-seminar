#include "car.hpp"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <utility>

unsigned Car::next_id = 1;

Car::Car(const char* brand, const char* model, double speed)
  : brand(new char[strlen(brand) + 1]{}),
    model(new char[strlen(model) + 1]{}),
    id(next_id++),
    traveled_distance(0),
    average_speed(speed),
    threshold_speed(speed / 2) {
  strcpy(this->brand, brand);
  strcpy(this->model, model);
}

Car::Car(const Car& other)
  : brand(new char[strlen(other.brand) + 1]{}),
    model(new char[strlen(other.model) + 1]{}),
    id(other.id),
    traveled_distance(other.traveled_distance),
    average_speed(other.average_speed),
    threshold_speed(other.threshold_speed) {
  strcpy(brand, other.brand);
  strcpy(model, other.model);
}

Car::~Car() {
  delete [] brand;
  delete [] model;
}

Car& Car::operator=(const Car& other) {
  Car copy(other);
  swap(copy);

  return *this;
}

double Car::drive(double distance) {
  double remaining = distance, hours = 0.0;

  while (remaining > 0) {
    double distance_to_drop = 100 - std::fmod(traveled_distance, 100);
    double segment = std::min(distance_to_drop, remaining);

    hours += segment / average_speed;
    traveled_distance += segment;
    remaining -= segment;

    if (std::fmod(traveled_distance, 100) < 1e-6 && !((average_speed - 1) < threshold_speed)) {
      --average_speed;
    }
  }

  return hours;
}

const char* Car::get_brand() const {
  return brand;
}

const char* Car::get_model() const {
  return model;
}

unsigned Car::get_id() const {
  return id;
}

double Car::get_average_speed() const {
  return average_speed;
}

double Car::get_traveled_distance() const {
  return traveled_distance;
}

void Car::swap(Car& other) {
  std::swap(brand, other.brand);
  std::swap(model, other.model);
  std::swap(id, other.id);
  std::swap(average_speed, other.average_speed);
  std::swap(threshold_speed, other.threshold_speed);
  std::swap(traveled_distance, other.traveled_distance);
}
