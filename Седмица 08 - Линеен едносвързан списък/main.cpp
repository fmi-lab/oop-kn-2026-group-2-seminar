#include <iostream>
#include <utility>

template <typename T>
class LinkedList {
public:
  LinkedList() : first(nullptr), last(nullptr) {}
  LinkedList(const LinkedList<T>& other) : first(nullptr), last(nullptr) {
    if (!other.first) {
      return;
    }

    first = last = new Node(other.first->data);
    Node* next = other.first->next;

    while (next) {
      last = last->next = new Node(next->data);
      next = next->next;
    }
  }
  ~LinkedList() {
    Node *next;
    while (first) {
      next = first->next;
      delete first;
      first = next;
    }
  }
  LinkedList<T>& operator=(const LinkedList<T>& other) {
    LinkedList<T> copy(other);
    swap(copy);

    return *this;
  }

  void insert_first(const T& element) {
    if (!first) {
      first = last = new Node(element);
      return;
    }

    first = new Node(element, first);
  }

  void reverse() {
    if (!first) {
      return;
    }

    Node *current = first, *prev = nullptr, *next;
    while (current) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
    }

    std::swap(first, last);
  }

private:
  struct Node {
    Node(const T& data, Node* next = nullptr) : data(data), next(next) {}

    T data;
    Node* next;
  };

public:
  class Iterator {
  public:
    Iterator(Node* node) : current(node) {}

    Iterator& operator++() {
      // current = current->next;
      // return *this;

      return *this = Iterator(current->next);
    }

    bool operator!=(const Iterator& other) const {
      return current != other.current;
    }

    bool operator==(const Iterator& other) const {
      return !(*this != other);
    }

    T& operator*() {
      return current->data;
    }

    const T& operator*() const {
      return current->data;
    }

    operator Node*() const {
      return current;
    }

  private:
    Node* current;
  };

  Iterator begin() const {
    return Iterator(first);
  }

  Iterator end() const {
    return Iterator(nullptr);
  }

  void insert_before(const T& element, const Iterator& pos) {
    if (pos == begin()) {
      insert_first(element);
      return;
    }
    
    Node* prev = before(pos);
    prev->next = new Node(element, pos);
  }

private:
  Node *first, *last;

  void swap(LinkedList<T>& other) {
    std::swap(first, other.first);
    std::swap(last, other.last);
  }

  Node* before(Node* node) const {
    Node* current = first;

    while (current && current->next != node) {
      current = current->next;
    }

    return current;
  }
};

int main() {
  LinkedList<int> list;

  list.insert_first(3);
  list.insert_first(2);
  list.insert_first(1);

  LinkedList<int>::Iterator begin = list.begin();
  ++begin;

  list.insert_before(4, begin);

  list.reverse();

  for (int x : list) {
    std::cout << x << ' ';
  }

  // LinkedList<int>::Iterator begin = list.begin();
  // LinkedList<int>::Iterator end = list.end();
  // for (; begin != end; ++begin) {
  //   int x = *begin;
  //   std::cout << x << ' ';
  // }
  
  std::cout << '\n';
  return 0;
}