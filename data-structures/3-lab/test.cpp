#define CATCH_CONFIG_MAIN

#include "graph.h"
#include "catch.hpp"

void deleteTwoDimensionalArray(int** array) {
  for (int i = 0;; i++) {
    if (array[i] == nullptr) {
      delete array[i];
      break;
    }
    delete [] array[i];
  }
  delete [] array;
}

TEST_CASE("insert weighted arrow, then erase it") {
  Graph g(2);
  g.insert(0, 1, 1);
  REQUIRE(g.erase(0, 1, 1) == true);
}

TEST_CASE(
  "insert two weighted arrows with the same associated vertices, "
  "then erase them with 1 erase(int, int) method call"
) {
  Graph g(2);
  g.insert(0, 1, 1);
  g.insert(0, 1, 2);
  REQUIRE(g.erase(0, 1) == 2);
}

TEST_CASE(
  "insert two weighted arrows with the same associated vertices, "
  "then erase them with 2 erase(int, int, int) method call"
) {
  Graph g(2);
  g.insert(0, 1, 1);
  g.insert(0, 1, 2);
  REQUIRE(g.erase(0, 1, 1) == true);
  REQUIRE(g.erase(0, 1, 2) == true);
}

TEST_CASE(
  "insert two unweighted arrows with the same associated vertices, "
  "then erase them with 1 erase(int, int) method call"
) {
  Graph g(2);
  g.insert(0, 1);
  g.insert(0, 1);
  REQUIRE(g.erase(0, 1) == 2);
}

TEST_CASE(
  "insert two unweighted arrows with the same associated vertices, "
  "then erase them with 2 erase(int, int, int) method call"
) {
  Graph g(2);
  g.insert(0, 1);
  g.insert(0, 1);
  REQUIRE(g.erase(0, 1, 1) == true);
  REQUIRE(g.erase(0, 1, 1) == true);
}

TEST_CASE("erase nonexistent arrow") {
  Graph g(1);
  REQUIRE(g.erase(0, 0) == false);
}

TEST_CASE("try to create graph with negative number of vertices") {
  try {
    Graph g(-1);
    REQUIRE(false);
  } catch(std::range_error& e) {
    REQUIRE(true);
  }
}

TEST_CASE("insert arrow with invalid numbers of associated vertices") {
  Graph g(3);
  try {
    g.insert(0, -1);
    REQUIRE(false);
  } catch(std::range_error& e) {
    REQUIRE(true);
  }
  try {
    g.insert(0, 3);
    REQUIRE(false);
  } catch(std::range_error& e) {
    REQUIRE(true);
  }
}

TEST_CASE("erase arrow with invalid numbers of associated vertices") {
  Graph g(3);
  try {
    g.erase(0, -1);
    REQUIRE(false);
  } catch(std::range_error& e) {
    REQUIRE(true);
  }
  try {
    g.erase(0, 3);
    REQUIRE(false);
  } catch(std::range_error& e) {
    REQUIRE(true);
  }
}

TEST_CASE("hamiltonian cycles in complete graph") {
  int output[24][5] = {
    { 0, 1, 2, 3, 4 }, { 0, 1, 2, 4, 3 }, { 0, 1, 3, 2, 4 }, { 0, 1, 3, 4, 2 },
    { 0, 1, 4, 2, 3 }, { 0, 1, 4, 3, 2 }, { 0, 2, 1, 3, 4 }, { 0, 2, 1, 4, 3 },
    { 0, 2, 3, 1, 4 }, { 0, 2, 3, 4, 1 }, { 0, 2, 4, 1, 3 }, { 0, 2, 4, 3, 1 },
    { 0, 3, 1, 2, 4 }, { 0, 3, 1, 4, 2 }, { 0, 3, 2, 1, 4 }, { 0, 3, 2, 4, 1 },
    { 0, 3, 4, 1, 2 }, { 0, 3, 4, 2, 1 }, { 0, 4, 1, 2, 3 }, { 0, 4, 1, 3, 2 },
    { 0, 4, 2, 1, 3 }, { 0, 4, 2, 3, 1 }, { 0, 4, 3, 1, 2 }, { 0, 4, 3, 2, 1 }
  };
  Graph g(5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) g.insert(i, j);
  }
  int** cycles = g.getAllHamiltonianCycles();
  for (int i = 0; cycles[i] != nullptr || i < 24; i++) {
    for (int j = 0; j < 5; j++) REQUIRE(cycles[i][j] == output[i][j]);
  }
  deleteTwoDimensionalArray(cycles);
}

TEST_CASE("hamiltonian cycles in tree") {
  Graph g(5);
  int input[8][2] = {
    { 0, 1 }, { 0, 2 }, { 1, 3 }, { 1, 4 },
    { 1, 0 }, { 2, 0 }, { 3, 1 }, { 4, 1 }
  };
  for (int i = 0; i < 4; i++) g.insert(input[i][0], input[i][1]);
  int** cycles = g.getAllHamiltonianCycles();
  REQUIRE(cycles[0] == nullptr);
  deleteTwoDimensionalArray(cycles);
}

TEST_CASE("hamiltonian cycles in empty graph") {
  Graph g(5);
  int** cycles = g.getAllHamiltonianCycles();
  REQUIRE(cycles[0] == nullptr);
  deleteTwoDimensionalArray(cycles);
}

TEST_CASE("hamiltonian cycles in oriented cycle graph") {
  Graph g(5);
  for (int i = 0; i < 5; i++) g.insert(i, (i + 1) % 5);
  int **cycles = g.getAllHamiltonianCycles();
  for (int i = 0; i < 5; i++) REQUIRE(cycles[0][i] == i);
  REQUIRE(cycles[1] == nullptr);
  deleteTwoDimensionalArray(cycles);
}

TEST_CASE("hamiltonian cycles in oriented cycle graph with multiple arrows") {
  Graph g(5);
  for (int i = 0; i < 5; i++) g.insert(i, (i + 1) % 5);
  g.insert(4, 0);
  int **cycles = g.getAllHamiltonianCycles();
  for (int i = 0; i < 5; i++) {
    REQUIRE(cycles[0][i] == i);
    REQUIRE(cycles[1][i] == i);
  }
  REQUIRE(cycles[2] == nullptr);
  deleteTwoDimensionalArray(cycles);
}

TEST_CASE("hamiltonian cycles in random graph") {
  int input[8][2] = {
    { 0, 1 }, { 0, 2 }, { 1, 2 }, { 1, 3 },
    { 2, 1 }, { 2, 3 }, { 3, 4 }, { 4, 0 }
  };
  int output[2][5] = {{ 0, 1, 2, 3, 4 }, { 0, 2, 1, 3, 4 }};
  Graph g(5);
  for (int i = 0; i < 8; i++) g.insert(input[i][0], input[i][1]);
  int** cycles = g.getAllHamiltonianCycles();
  for (int i = 0; cycles[i] != nullptr || i < 2; i++) {
    for (int j = 0; j < 5; j++) REQUIRE(cycles[i][j] == output[i][j]);
  }
  deleteTwoDimensionalArray(cycles);
}
