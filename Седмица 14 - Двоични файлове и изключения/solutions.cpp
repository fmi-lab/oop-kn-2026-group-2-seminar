#include <cstddef>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <limits>

class Book {
private:
  static constexpr std::size_t MAX_NAME_SIZE = 100;
  static constexpr std::size_t MAX_AUTHOR_SIZE = 50;

public:
  Book(const char name[MAX_NAME_SIZE] = "", const char author[MAX_AUTHOR_SIZE] = "", unsigned id = 0)
    : id(id) {
    strcpy(this->name, name);
    strcpy(this->author, author);
  }

  void serialize(std::ostream& file) const {
    file << name << '\n' << author << '\n' << id << '\n';
  }

  void deserialize(std::istream& file) {
    if (file.peek() == '\n') {
      file.ignore();
    }
    file.getline(name, MAX_NAME_SIZE);
    file.getline(author, MAX_AUTHOR_SIZE);
    file >> id;
  }
  
  void serialize_binary(std::ostream& file) const {
    // file.write(name, MAX_NAME_SIZE);
    // file.write(author, MAX_AUTHOR_SIZE);
    // file.write(reinterpret_cast<const char*>(&id), sizeof(id));

    file.write(reinterpret_cast<const char*>(this), sizeof(Book));
  }

  void deserialize_binary(std::istream& file) {
    // file.read(name, MAX_NAME_SIZE);
    // file.read(author, MAX_AUTHOR_SIZE);
    // file.read(reinterpret_cast<char*>(&id), sizeof(id));

    file.read(reinterpret_cast<char*>(this), sizeof(Book));
  }

  void serialize_at(std::ostream &os, std::size_t pos) const {
    os.seekp(0, std::ios::end);
    std::streampos size = os.tellp();
    unsigned book_size = sizeof(Book); //sizeof(name) + sizeof(author) + sizeof(id);
    std::size_t books_count = size / book_size;

    if (pos <= books_count) {
      os.seekp((pos - 1) * book_size);
      serialize_binary(os);
    }
  }

  void deserialize_at(std::istream &is, std::size_t pos) {
    is.seekg(0, std::ios::end);
    std::streampos size = is.tellg();
    unsigned book_size = sizeof(Book); //sizeof(name) + sizeof(author) + sizeof(id);
    std::size_t books_count = size / book_size;

    if (pos <= books_count) {
      is.seekg((pos - 1) * book_size);
      deserialize_binary(is);
    }
  }  

private:
  char name[MAX_NAME_SIZE], author[MAX_AUTHOR_SIZE];
  unsigned id;
};

int main() {
  Book book1, book2;
  std::ifstream input("input.txt");
  if (!input) {
    return 1;
  }
  int i;

  book1.deserialize(input);
  input >> i;
  std::cout << i << '\n';
  book2.deserialize(input);

  input.close();
  
  // std::ofstream output("output.txt");
  
  // book1.serialize(output);
  // book2.serialize(output);
  
  // output.close();

  // ======================================

  input.open("input.bin", std::ios::binary);

  if (!input) {
    return 1;
  }

  book1.deserialize_binary(input);
  book2.deserialize_binary(input);

  input.close();

  std::ofstream output("output.txt");

  if (!output) {
    return 1;
  }

  book1.serialize(output);
  book2.serialize(output);

  output.close();
  return 0;
}