#include <cstddef>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>

class MathExpression {
public:
  virtual float evaluate() const = 0;
  virtual std::ostream& print(std::ostream& = std::cout) const = 0;
  virtual MathExpression* clone() const = 0;
  virtual ~MathExpression() = default;
};

class Constant : public MathExpression {
public:
  Constant(float value) : value(value) {}

  float evaluate() const final {
    return value;
  }

  std::ostream& print(std::ostream& os = std::cout) const final {
    return os << value;
  }

  Constant* clone() const final {
    return new Constant(*this);
  }

private:
  float value;
};

class Sum : public MathExpression {
public:
  Sum() = default;

  Sum(const Sum& other) {
    for (const MathExpression* const expression : other.expressions) {
      expressions.push_back(expression->clone());
    }
  }

  ~Sum() {
    for (MathExpression* expression : expressions) {
      delete expression;
    }
  }

  Sum& operator=(const Sum& other) {
    Sum copy(other);
    swap(copy);

    return *this;
  }

  Sum& add(const MathExpression& expression) {
    expressions.push_back(expression.clone());
    return *this;
  }

  float evaluate() const {
    float sum = 0.0;

    for (const MathExpression* expression : expressions) {
      sum += expression->evaluate();
    }

    return sum;
  }

  std::ostream& print(std::ostream& os = std::cout) const {
    if (expressions.empty()) {
      return os;
    }

    os << '(';
    expressions[0]->print(os);
    for (std::size_t i = 1; i < expressions.size(); ++i) {
      os << " + ";
      expressions[i]->print(os);
    }
    return os << ')';
  }

  Sum* clone() const {
    return new Sum(*this); 
  }

private:
  std::vector<MathExpression*> expressions;

  void swap(Sum& other) {
    std::swap(expressions, other.expressions);
  }
};

class Power : public MathExpression {
public:
  Power(const MathExpression& expression, int exponent)
    : expression(expression.clone()),
      exponent(exponent) {}

  Power(const Power& other)
    : expression(other.expression->clone()),
      exponent(other.exponent) {}

  ~Power() {
    delete expression;
  }

  Power& operator=(const Power& other) {
    Power copy(other);
    swap(copy);

    return *this;
  }

  float evaluate() const {
    int current_exponent = exponent;
    float result = 1, base = expression->evaluate();

    if (current_exponent < 0) {
      base = 1 / base;
      current_exponent = -current_exponent;
    }

    while (current_exponent > 0) {
      if (current_exponent % 2 == 0) {
        base *= base;
        current_exponent /= 2;
      } else {
        result *= base;
        --current_exponent;
      }
    }

    return result;
  }

  std::ostream& print(std::ostream& os = std::cout) const {
    return expression->print(os) << '^' << exponent;
  }

  Power* clone() const {
    return new Power(*this);
  }

private:
  MathExpression* expression;
  int exponent;

  void swap(Power& other) {
    std::swap(expression, other.expression);
    std::swap(exponent, other.exponent);
  }
};

int main() {
  Constant c1(5), c2(6), c3(8);
  Sum s1;
  s1.add(c1);

  Sum s2;
  s2.add(c2).add(c3);

  s1.add(s2);

  s1.print() << '\n';
  std::cout << s1.evaluate() << '\n';

  Power p(c1, -5);
  std::cout << p.evaluate() << '\n';
  p.print() << '\n';
  return 0;
}