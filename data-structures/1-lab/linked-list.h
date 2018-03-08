#ifndef LINKED_LIST_H
#define LINKED_LIST_H

template <class T>
class Node {
public:
  T data;
  Node<T>* prev;
  Node<T>* next;
  Node(T data): prev(nullptr), next(nullptr), data(data) {}
  ~Node() {}
};

template <class T>
class List {
private:
  int length;
  Node<T>* first;
  Node<T>* last;
  Node<T>* findNodeByPos(int);
public:
  List();
  ~List();
  Node<T>* begin();
  Node<T>* end();
  T insert(T, int);
  T erase(int);
  T peek(int);
};

#include "linked-list.cpp"

#endif
