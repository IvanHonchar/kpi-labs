#ifndef BIN_TREE_H
#define BIN_TREE_H

template <class T>
class BinTree {
private:
  class Node {
  public:
    T value;
    Node* left;
    Node* right;

    Node(T value):
      value(value),
      left(nullptr),
      right(nullptr)
    {}

    ~Node() {}
  };

  void insert(Node* node, T value) {
    if (value < node->value && node->left) return insert(node->left, value);
    if (value < node->value) node->left = new Node(value);
    if (value > node->value && node->right) return insert(node->right, value);
    if (value > node->value) node->right = new Node(value);
  }

  void erase(Node* node, Node* parent, T value) {
    if (value < node->value) return erase(node->left, node, value);
    if (value > node->value) return erase(node->right, node, value);
    if (value != node->value) return;
    if (node->left && node->right) {
      Node* current = node->right;
      parent = node;
      while (current->left != nullptr) {
        parent = current;
        current = current->left;
      }
      node->value = current->value;
      node = current;
    }
    Node* child = node->left ? node->left : node->right;
    if (parent) {
      if (parent->left == node) parent->left = child;
      else parent->right = child;
    } else root = child;
    delete node;
  }

  bool find(Node* node, T value) {
    if (!node) return false;
    if (value < node->value) return find(node->left, value);
    if (value > node->value) return find(node->right, value);
    if (value == node->value) return true;
  }

  int count;
  Node* root;

public:
  BinTree(): root(nullptr), count(0) {}

  ~BinTree() {
    clear();
  }

  void clear() {
    while (root) erase(root->value);
  }

  void insert(T value) {
    if (find(value)) return;
    count++;
    if (!root) root = new Node(value);
    else insert(root, value);
  }

  void erase(T value) {
    if (!find(value)) return;
    count--;
    erase(root, nullptr, value);
  }


  bool find(T value) {
    return find(root, value);
  }

  int size() {
    return count;
  }

  int getNodeDepthByValue(T value) {
    if (!find(value)) return -1;
    int depth = 1;
    Node* current = root;
    while (current->value != value) {
      depth++;
      current = (value < current->value) ? current->left : current->right;
    }
    return depth;
  }

  int depth(Node* current = nullptr) {
    if (!root) return 0;
    if (!current) current = root;
    int leftDepth = current->left ? depth(current->left) : 0;
    int rightDepth = current->right ? depth(current->right) : 0;
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
  }
};

#endif
