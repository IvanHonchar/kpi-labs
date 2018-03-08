#include "linked-list.h"
#include <stdexcept>

template <class T>
Node<T>* List<T>::findNodeByPos(int pos) {
  if (pos > length || pos <= 0) {
    throw std::invalid_argument("Invalid argument pos");
  }
  int i = 1;
  Node<T>* cur = first;
  while (i < pos) {
    i++;
    cur = cur->next;
  }
  return cur;
}

template <class T>
List<T>::List(): first(nullptr), last(nullptr), length(0) {}

template <class T>
List<T>::~List() {
  Node<T>* cur = first;
  while (cur != nullptr) {
    Node<T>* prev = cur;
    cur = cur->next;
    delete prev;
  }
}

template <class T>
Node<T>* List<T>::begin() {
    return first;
}

template <class T>
Node<T>* List<T>::end() {
  return last;
}

template <class T>
T List<T>::insert(T data, int pos) {
  Node<T>* node = new Node<T>(data);
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
  return data;
}

template <class T>
T List<T>::erase(int pos) {
  Node<T>* node = findNodeByPos(pos);
  if (pos == 1) first = node->next;
  if (pos == length) last = node->prev;
  if (node->prev) node->prev->next = node->next;
  if (node->next) node->next->prev = node->prev;
  T data = node->data;
  delete node;
  length--;
  return data;
}

template <class T>
T List<T>::peek(int pos) {
  return findNodeByPos(pos)->data;
}
