#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <string>
#include <stdexcept>

template <class T>
class List {
private:
  class Node {
  public:
    T data;
    Node* prev;
    Node* next;
    Node(T data): prev(nullptr), next(nullptr), data(data) {}
    ~Node() {}
  };

  int length;
  Node* first;
  Node* last;

  Node* findNodeByPos(int pos) {
    if (pos > length || pos <= 0) throw std::range_error(
      "element with " + std::to_string(pos) + " position doesn't exist"
    );
    Node* current = first;
    while (pos > 1) {
      current = current->next;
      pos--;
    }
    return current;
  }

  T erase(Node* node) {
    if (!node->prev) first = node->next;
    if (!node->next) last = node->prev;
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    T data = node->data;
    delete node;
    length--;
    return data;
  }

public:
  class iterator {
    friend List;

  private:
    Node* node;

  public:
    iterator(Node* node): node(node) {}

    iterator(const iterator& it): node(it.node) {}

    ~iterator() {}

    bool operator!=(iterator const& other) const {
      return node != other.node;
    }

    bool operator==(iterator const& other) const {
      return node == other.node;
    }

    iterator& operator++() {
      if (!node) throw std::range_error(
        "iteration over the list has already been done"
      );
      node = node->next;
      return *this;
    }

    iterator& operator--() {
      if (!node) throw std::range_error(
        "iteration over the list has already been done"
      );
      node = node->prev;
      return *this;
    }

    T& operator*() {
      return node->data;
    }

    T* operator->() {
      return &node->data;
    }
  };

  iterator begin() { return iterator(first); }
  iterator end() { return iterator(nullptr); }

  List(): first(nullptr), last(nullptr), length(0) {}

  ~List() {
    while (length > 0) erase(1);
  }

  iterator insert(T data, int pos) {
    Node* node = new Node(data);
    if (pos == 0) {
      node->next = first;
      first = node;
    } else {
      node->prev = findNodeByPos(pos);
      node->next = node->prev->next;
      node->prev->next = node;
    }
    if (pos == length) last = node;
    else node->next->prev = node;
    length++;
    return iterator(node);
  }

  T erase(int pos) {
    return erase(findNodeByPos(pos));
  }

  T erase(iterator it) {
    return erase(it.node);
  }

  T peek(int pos) {
    return findNodeByPos(pos)->data;
  }

  int size() {
    return length;
  }
};

#endif
