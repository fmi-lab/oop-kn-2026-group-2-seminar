#include <cstring>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../libs/doctest.h"
#include "car.hpp"

class CarFixture {
public:
  CarFixture()
    : car(brand, model, 120) {}

protected:
  const char* brand = "Mitsubishi";
  const char* model = "Lancer Evolution 6";
  Car car;
};

TEST_SUITE("Car") {
  TEST_CASE("constructor") {
    SUBCASE("correctly initializes the object") {
      const char* brand = "Nissan";
      const char* model = "GT-R 35";
      Car car(brand, model, 90);

      CHECK(strcmp(brand, car.get_brand()) == 0);
      CHECK(strcmp(model, car.get_model()) == 0);
      CHECK_EQ(car.get_average_speed(), doctest::Approx(90));
      CHECK_EQ(car.get_traveled_distance(), doctest::Approx(0));
      CHECK_EQ(car.get_id(), 1);
    }

    SUBCASE("correctly increments id for every new car") {
      Car car1("Mazda", "RX-7 FD", 90);
      Car car2("Toyota", "GR 86", 120);

      CHECK_EQ(car1.get_id() + 1, car2.get_id());
    }
  }

  TEST_CASE_FIXTURE(CarFixture, "copy constructor") {
    SUBCASE("copies car correctly") {
      Car copy(car);

      CHECK_EQ(strcmp(copy.get_brand(), car.get_brand()), 0);
      CHECK_EQ(strcmp(copy.get_model(), car.get_model()), 0);
      CHECK_EQ(copy.get_average_speed(), car.get_average_speed());
      CHECK_EQ(copy.get_traveled_distance(), car.get_traveled_distance());
      CHECK_EQ(copy.get_id(), car.get_id());
    }

    SUBCASE("makes deep copy of car") {
      Car* copy = new Car(car);
      delete copy;

      CHECK(strcmp(brand, car.get_brand()) == 0);
      CHECK(strcmp(model, car.get_model()) == 0);
    }
  }

  TEST_CASE_FIXTURE(CarFixture, "drive") {
    SUBCASE("correctly calculates time for distance less than 100km") {
      double time = car.drive(90);
      
      CHECK_EQ(time, doctest::Approx(0.75));
      CHECK_EQ(car.get_traveled_distance(), doctest::Approx(90));
    }

    SUBCASE("correctly calculates time for distance above 100km") {
      double time = car.drive(250);

      CHECK_EQ(time, doctest::Approx(2.097).epsilon(1e-3));
      CHECK_EQ(car.get_traveled_distance(), doctest::Approx(250));
    }

    SUBCASE("correctly calculates total distance when calling drive multiple times") {
      car.drive(90);
      car.drive(250);

      CHECK_EQ(car.get_traveled_distance(), doctest::Approx(340));
    }

    SUBCASE("does not change anything if distance is 0km") {
      double time = car.drive(0);

      CHECK_EQ(time, doctest::Approx(0));
      CHECK_EQ(car.get_traveled_distance(), doctest::Approx(0));
    }

    SUBCASE("does not change anything if distance is less than 0km") {
      double time = car.drive(-120);

      CHECK_EQ(time, doctest::Approx(0));
      CHECK_EQ(car.get_traveled_distance(), doctest::Approx(0));
    }

    SUBCASE("does not drop speed below half of the original") {
      car.drive(6'500);

      CHECK_EQ(car.get_average_speed(), doctest::Approx(60));
    }
  }
}