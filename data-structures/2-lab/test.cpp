#define CATCH_CONFIG_MAIN

#include "bin-tree.h"
#include "catch.hpp"

TEST_CASE("tree size after initialize") {
  BinTree<int> t;
  REQUIRE(t.size() == 0);
  REQUIRE(t.depth() == 0);
}

TEST_CASE("insert 1 element, then erase it") {
  BinTree<int> t;
  t.insert(1);
  REQUIRE(t.find(1) == true);
  REQUIRE(t.size() == 1);
  t.erase(1);
  REQUIRE(t.find(1) == false);
  REQUIRE(t.size() == 0);
  REQUIRE(t.depth() == 0);
}

TEST_CASE("insert 2 equal elements, then erase it") {
  BinTree<int> t;
  t.insert(2);
  t.insert(2);
  REQUIRE(t.find(2) == true);
  REQUIRE(t.size() == 1);
  t.erase(2);
  REQUIRE(t.find(2) == false);
  REQUIRE(t.size() == 0);
  REQUIRE(t.depth() == 0);
}

TEST_CASE("insert 10 elements, getNodeDepthByValue of each") {
  BinTree<int> t;
  int array[10] = { 28, 5, 32, 92, 33, 64, 60, 6, 56, 41 };
  int depth[10] = { 1, 2, 2, 3, 4, 5, 6, 3, 7, 8 };
  for (int i = 0; i < 10; i++) t.insert(array[i]);
  for (int i = 0; i < 10; i++) REQUIRE(t.find(array[i]) == true);
  for (int i = 0; i < 10; i++) REQUIRE(t.getNodeDepthByValue(array[i]) == depth[i]);
  REQUIRE(t.depth() == 8);
}

TEST_CASE("random insertings and erasings") {
  BinTree<int> t;
  int array[20] = {
    28, 5, 32, 92, 33, 64, 60, 6, 56, 41, 82, 84, 73, 49, 15, 50, 5, 12, 47, 81
  };
  t.insert(28);
  t.insert(5);
  t.insert(5);
  t.insert(32);
  t.insert(4);
  t.insert(6);
  t.erase(28);
  t.erase(5);
  t.erase(50);
  t.insert(5);
  t.insert(60);
  t.insert(56);
  t.insert(58);
  t.insert(90);
  REQUIRE(t.getNodeDepthByValue(28) == -1);
  REQUIRE(t.getNodeDepthByValue(32) == 1);
  REQUIRE(t.getNodeDepthByValue(6) == 2);
  REQUIRE(t.getNodeDepthByValue(60) == 2);
  REQUIRE(t.getNodeDepthByValue(4) == 3);
  REQUIRE(t.getNodeDepthByValue(56) == 3);
  REQUIRE(t.getNodeDepthByValue(90) == 3);
  REQUIRE(t.getNodeDepthByValue(5) == 4);
  REQUIRE(t.getNodeDepthByValue(58) == 4);
  REQUIRE(t.size() == 8);
  REQUIRE(t.depth() == 4);
  t.clear();
  REQUIRE(t.size() == 0);
  REQUIRE(t.depth() == 0);
}
