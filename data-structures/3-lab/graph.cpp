#include "graph.h"

class Graph::Arrow {
public:
 int to;
 int weight;
 Arrow(int to, int weight): to(to), weight(weight) {}
 ~Arrow() {}
};

Graph::Graph(int n) {
  if (n < 1) throw std::range_error("graph can't contain less than one vetex");
  verticesNumber = n;
  adList = new List<Arrow> [verticesNumber];
}

Graph::~Graph() {
  delete [] adList;
}

void Graph::isValidVertexNumber(int number) {
  if (number < 0 || number >= verticesNumber) throw std::range_error(
    "vertex with " + std::to_string(number) + " number doesn't exist"
  );
}

void Graph::insert(int from, int to, int weight) {
  isValidVertexNumber(from);
  isValidVertexNumber(to);
  adList[from].insert(Arrow(to, weight), 0);
}

bool Graph::erase(int from, int to, int weight) {
  isValidVertexNumber(from);
  isValidVertexNumber(to);
  for (auto i = adList[from].begin(); i != adList[from].end(); ++i) {
    auto& arrow = *i;
    if (arrow.to == to && arrow.weight == weight) {
      adList[from].erase(i);
      return true;
    }
  }
  return false;
}

int Graph::erase(int from, int to) {
  isValidVertexNumber(from);
  isValidVertexNumber(to);
  int erased = 0;
  List<List<Arrow>::iterator> toErase;
  for (auto i = adList[from].begin(); i != adList[from].end(); ++i) {
    auto& arrow = *i;
    if (arrow.to == to) {
      toErase.insert(i, 0);
      erased++;
    }
  }
  for (auto& element : toErase) adList[from].erase(element);
  return erased;
}

int** Graph::getAllHamiltonianCycles() {
  List<int*> answerList;
  bool* passed = new bool [verticesNumber];
  int* path = new int [verticesNumber];
  for (int i = 0; i < verticesNumber; i++) passed[i] = false;
  getAllHamiltonianCycles(0, 0, passed, path, answerList);
  int** answer = new int* [answerList.size() + 1];
  answer[answerList.size()] = nullptr;
  for (int i = 0; answerList.size() > 0; i++) {
    answer[i] = answerList.erase(1);
  }
  delete [] passed;
  delete [] path;
  return answer;
}

void Graph::getAllHamiltonianCycles(
  int current,
  int currentNumber,
  bool* passed,
  int* path,
  List<int*>& answerList
) {
  passed[current] = true;
  path[currentNumber] = current;
  if (currentNumber == verticesNumber - 1) {
    for (auto& arrow : adList[current]) if (arrow.to == 0) {
      int* newPath = new int [verticesNumber];
      for (int i = 0; i < verticesNumber; i++) newPath[i] = path[i];
      answerList.insert(newPath, 0);
    }
  } else {
    for (auto& arrow : adList[current]) {
      if (!passed[arrow.to]) getAllHamiltonianCycles(
        arrow.to, currentNumber + 1, passed, path, answerList
      );
    }
  }
  passed[current] = false;
}
