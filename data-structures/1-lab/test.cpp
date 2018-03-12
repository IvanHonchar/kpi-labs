#define CATCH_CONFIG_MAIN

#include "linked-list.h"
#include "catch.hpp"

TEST_CASE("pushing elements back") {
  List<int> list;
  for (int i = 0; i < 10; i++) list.insert(i, i);
  for (int i = 0; i < 10; i++) REQUIRE(list.peek(i + 1) == i);
}

TEST_CASE("pushing elements front") {
  List<int> list;
  for (int i = 0; i < 10; i++) list.insert(i, 0);
  for (int i = 10; i >= 1; i--) REQUIRE(list.peek(i) == 10 - i);
}

TEST_CASE("pushing elements back and erasing front") {
  List<int> list;
  for (int i = 0; i < 10; i++) list.insert(i, i);
  for (int i = 0; i < 10; i++) REQUIRE(list.erase(1) == i);
}

TEST_CASE("pushing elements front and erasing back") {
  List<int> list;
  for (int i = 0; i < 10; i++) list.insert(i, 0);
  for (int i = 10; i >= 1; i--) REQUIRE(list.erase(i) == 10 - i);
}

TEST_CASE("random insertings and erasings") {
  List<int> list;
  list.insert(0, 0);
  list.insert(1, 0);
  list.insert(2, 2);
  list.insert(3, 1);
  list.insert(4, 2);
  list.insert(5, 5);
  list.erase(3);
  list.erase(5);
  list.erase(1);
  REQUIRE(list.peek(1) == 3);
  REQUIRE(list.peek(2) == 0);
  REQUIRE(list.peek(3) == 2);
}
