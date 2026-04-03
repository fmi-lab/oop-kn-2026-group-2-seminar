#ifndef CAR_HPP
#define CAR_HPP

class Car {
public:
  Car(const char* brand, const char* model, double speed);
  Car(const Car& other);
  ~Car();
  Car& operator=(const Car& other);

  double drive(double distance);
  const char* get_brand() const;
  const char* get_model() const;
  unsigned get_id() const;
  double get_average_speed() const;
  double get_traveled_distance() const;

private:
  char *brand, *model;
  unsigned id;
  static unsigned next_id;
  double average_speed, threshold_speed, traveled_distance;

  void swap(Car& other);
};

#endif