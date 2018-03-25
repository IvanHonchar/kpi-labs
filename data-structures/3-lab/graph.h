#ifndef GRAPH_H
#define GRAPH_H

#include "linked-list.h"

class Graph {
private:
  class Arrow;
  List<Arrow>* adList;
  int verticesNumber;
  void isValidVertexNumber(int);
  void getAllHamiltonianCycles(int, int, bool*, int*, List<int*>&);
public:
  Graph(int);
  ~Graph();
  void insert(int, int, int = 1);
  bool erase(int, int, int);
  int erase(int , int);
  int** getAllHamiltonianCycles();
};

#endif
