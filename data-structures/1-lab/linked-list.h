template <class T>
class Node {
public:
  T data;
  Node<T>* prev;
  Node<T>* next;

  Node(T item) {
    prev = NULL;
    next = NULL;
    data = item;
  }
};

template <class T>
class List {
  int length;
  Node<T>* first;
  Node<T>* last;

  Node<T>* findNodeByPos(int pos) {
    int i = 1;
    Node<T>* cur = first;
    while (i < pos) {
      i++;
      cur = cur->next;
    }
    return cur;
  }

public:
  List() {
    first = last = NULL;
    length = 0;
  }

  Node<T>* begin() {
    return first;
  }

  Node<T>* end() {
    return last;
  }

  void insert(T item, int pos) {
    if (pos > length || pos < 0) {
      throw "Invalid argument pos";
      return;
    }

    Node<T>* node = new Node<T>(item);

    if (length == 0) {
      first = last = node;
    } else if (pos == 0) {
      first->prev = node;
      node->next = first;
      first = node;
    } else if (pos == length) {
      last->next = node;
      node->prev = last;
      last = node;
    } else {
      node->prev = findNodeByPos(pos);
      node->next = node->prev->next;
      node->prev->next = node;
      node->next->prev = node;
    }

    length++;
  }
};
