#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <ostream>

class Character {
public:
  Character(const char* name = "", double damage = 0.0, double health = 0.0)
    : name(new char[strlen(name) + 1]{}), damage(damage), health(health) {
    strcpy(this->name, name);
  }

  Character(const Character& other)
    : name(new char[strlen(other.name) + 1]{}), damage(other.damage), health(other.health) {
    strcpy(name, other.name);
  }

  virtual ~Character() {
    delete [] name;
  }

  virtual Character* clone() const {
    return new Character(*this);
  }

  Character& operator=(const Character& other) {
    Character copy(other);
    swap(copy);

    return *this;
  }

  void deal_damage_to(Character& other) const {
    other.take_damage(attack_damage());
  }
  
  virtual void take_damage(double points) {
    health = std::max(health - points, 0.0);
  }

  virtual void heal(double points) {
    health += points;
  }

  bool operator==(const char* name) const {
    return strcmp(this->name, name) == 0;
  }

  std::ostream& print(std::ostream& os = std::cout) const {
    return os << "Name: " << name << '\n'
              << "Type: " << type() << "\n"
              << "HP: " << health << '\n'
              << "DMG: " << damage;
  }

protected:
  virtual double attack_damage() const {
    return damage;
  }

private:
  char* name;
  double damage, health;

  void swap(Character& other) {
    std::swap(name, other.name);
    std::swap(damage, other.damage);
    std::swap(health, other.health);
  }

  virtual const char* type() const {
    return "Ordinary Character";
  }
};

class Knight : public Character {
public:
  Knight(const char* name = "", double damage = 0.0, double health = 0.0)
    : Character(name, damage, health) {}

  void take_damage(double points) final {
    Character::take_damage(points * 0.75);
  }

  void heal(double points) final {
    Character::heal(points * 1.05);
  }

  Knight* clone() const final {
    return new Knight(*this);
  }

private:
  const char* type() const final {
    return "Knight";
  }
};

class Archer : public Character {
public:
  Archer(const char* name = "", double damage = 0.0, double health = 0.0)
    : Character(name, damage, health) {}

  void take_damage(double points) final {
    Character::take_damage(points * 1.15);
  }

  Archer* clone() const final {
    return new Archer(*this);
  }

private:
  const char* type() const final {
    return "Archer";
  }

  double attack_damage() const final {
    return Character::attack_damage() * 1.33;
  }
};

class Game {
public:
  Game() : characters(nullptr), size(0), capacity(0) {}
  Game(const Game& other)
    : characters(new Character*[other.capacity]),
      size(other.size),
      capacity(other.capacity) {
    for (std::size_t i = 0; i < size; ++i) {
      characters[i] = other.characters[i]->clone();
    }
  }
  ~Game() {
    for (std::size_t i = 0; i < size; ++i) {
      delete characters[i];
    }
    delete [] characters;
  }
  Game& operator=(const Game& other) {
    Game copy(other);
    swap(copy);

    return *this;
  }

  void add(const Character& character) {
    if (size == capacity) {
      resize();
    }

    characters[size++] = character.clone();
  }

  void print() const {
    for (std::size_t i = 0; i < size; ++i) {
      characters[i]->print() << '\n' << '\n';
    }
  }

  void heal(double amount) {
    for (std::size_t i = 0; i < size; ++i) {
      characters[i]->heal(amount);
    }
  }

  void battle(const char* attacker, const char* target) {
    Character* attacking_character = find(attacker);
    if (!attacking_character) {
      std::cout << "Invalid attacker with name: " << attacker << '\n';
      return;
    }

    Character* target_character = find(target);
    if (!target_character) {
      std::cout << "Invalid target with name: " << target << '\n';
      return;
    }

    attacking_character->deal_damage_to(*target_character);

    // TODO: check if dead
  }

private:
  Character** characters;
  std::size_t size, capacity;

  void swap(Game& other) {
    std::swap(characters, other.characters);
    std::swap(size, other.size);
    std::swap(capacity, other.capacity);
  }

  void resize() {
    if (capacity == 0) {
      capacity = 1;
    }

    Character** new_characters = new Character*[capacity *= 2];
    for (std::size_t i = 0; i < size; ++i) {
      new_characters[i] = characters[i];
    }

    delete [] characters;
    characters = new_characters;
  }

  Character* find(const char* name) {
    for (std::size_t i = 0; i < size; ++i) {
      Character& character = *characters[i];
      
      if (character == name) {
        return &character;
      }
    }

    return nullptr;
  }
};

int main() {
  Character c("Archibald", 20, 100);
  Knight k("Arthur", 30, 150);
  Archer a("Legolas", 50, 80);

  Game game;
  game.add(c);
  game.add(k);
  game.add(a);

  game.heal(20);
  
  game.battle("Legolas", "Arthur");
  game.print();

  return 0;
}