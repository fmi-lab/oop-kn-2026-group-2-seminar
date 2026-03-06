#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
#include <type_traits>

class Student {
public:
  Student(const char* name, int year, int group, int fn, double average_grade) 
    : name(new char[strlen(name)+1]{}),
      year(year),
      group(group),
      fn(fn),
      grades(nullptr),
      size(0),
      capacity(0) {
    strcpy(this->name, name);
  }

  Student(const Student& other)
    : name(new char[strlen(other.name)+1]{}),
      year(other.year),
      group(other.group),
      fn(other.fn),
      grades(new double[other.capacity]{}),
      size(other.size),
      capacity(other.capacity) {
    strcpy(name, other.name);
    for (std::size_t i = 0; i < other.size; ++i) {
      grades[i] = other.grades[i];
    }
  }

  void add_grade(double grade) {
    if (size == capacity) {
      // TODO: resize
    }

    grades[size++] = grade;
  } 

  Student& operator=(const Student& other) {
    // if (this != &other) {
    //   delete [] name;
    //   name = new char[strlen(other.name) + 1]{};
    //   strcpy(name, other.name);
    //   year = other.year;
    //   group = other.group;
    //   fn = other.fn;
    //   average_grade = other.average_grade;
    // }

    Student copy(other);
    swap(copy);

    return *this;
  }

  ~Student() {
    delete [] name;
    delete [] grades;
  }

  void info() const {
    std::cout << "Name: " << name << '\n'
              << "Year: " << year << '\n'
              << "Group: " << group << '\n'
              << "Faculty number: " << fn << '\n';
  }

  Student& swap(Student& other) {
    using std::swap;
    swap(name, other.name);
    swap(year, other.year);
    swap(group, other.group);
    swap(fn, other.fn);
    swap(grades, other.grades);
    swap(size, other.size);
    swap(capacity, other.capacity);

    return *this;
  }

private:
  char* name;
  int year, group, fn;
  double* grades;
  std::size_t size, capacity;
};

int main() {
  char name[] = "Ivan";
  Student student(name, 1, 3, 82014, 5.75);
  name[0] = 'G';
  student.info();

  Student copy(student);

  // Student copy = student;
  std::cout << '\n';
  copy.info();

  copy = copy;

  Student* s = new Student(name, 1, 3, 82014, 5.75);
  delete s;

  return 0;
}