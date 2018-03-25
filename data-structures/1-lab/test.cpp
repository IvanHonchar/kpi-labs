#define CATCH_CONFIG_MAIN

#include "linked-list.h"
#include "catch.hpp"

TEST_CASE("list size after initialize") {
  List<int> list;
  REQUIRE(list.size() == 0);
}

TEST_CASE("pushing elements back") {
  List<int> list;
  for (int i = 0; i < 10; i++) list.insert(i, i);
  for (int i = 0; i < 10; i++) REQUIRE(list.peek(i + 1) == i);
  REQUIRE(list.size() == 10);
}

TEST_CASE("pushing elements front") {
  List<int> list;
  for (int i = 0; i < 10; i++) list.insert(i, 0);
  for (int i = 10; i >= 1; i--) REQUIRE(list.peek(i) == 10 - i);
  REQUIRE(list.size() == 10);
}

TEST_CASE("pushing elements back and erasing front") {
  List<int> list;
  for (int i = 0; i < 10; i++) list.insert(i, i);
  for (int i = 0; i < 10; i++) REQUIRE(list.erase(1) == i);
  REQUIRE(list.size() == 0);
}

TEST_CASE("pushing elements front and erasing back") {
  List<int> list;
  for (int i = 0; i < 10; i++) list.insert(i, 0);
  for (int i = 10; i >= 1; i--) REQUIRE(list.erase(i) == 10 - i);
  REQUIRE(list.size() == 0);
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
  REQUIRE(list.size() == 3);
}

TEST_CASE("iterator and erase compability") {
  List<int> list;
  list.insert(1, 0);
  list.insert(2, 0);
  list.insert(3, 0);
  REQUIRE(list.erase(++list.begin()) == 2);
  REQUIRE(list.size() == 2);
}

TEST_CASE("iterators equality") {
  List<int> list;
  list.insert(0, 0);
  list.insert(0, 0);
  list.insert(0, 0);
  auto begin = list.begin();
  auto end = list.end();
  REQUIRE(begin == list.begin());
  REQUIRE(end == list.end());
  REQUIRE(begin != end);
}

TEST_CASE("iterator::operator* functionality") {
  List<int> list;
  list.insert(10, 0);
  auto i = list.begin();
  REQUIRE(*i == 10);
}

TEST_CASE("iterator::operator-> functionality") {
  struct Foo {
    int bar;
    Foo(int bar): bar(bar) {}
  };
  List<Foo> list;
  list.insert(Foo(10), 0);
  auto i = list.begin();
  REQUIRE(i->bar == 10);
  REQUIRE(i->bar == (*i).bar);
}

TEST_CASE("provoking exceptions in insert method") {
  List<int> list;
  try {
    list.insert(1, -1);
    REQUIRE(false);
  } catch (std::range_error& e) {
    REQUIRE(true);
  }
  try {
    list.insert(2, 1);
    REQUIRE(false);
  } catch (std::range_error& e) {
    REQUIRE(true);
  }
}

TEST_CASE("provoking exceptions in erase method") {
  List<int> list;
  try {
    list.erase(0);
    REQUIRE(false);
  } catch (std::range_error& e) {
    REQUIRE(true);
  }
  try {
    list.erase(2);
    REQUIRE(false);
  } catch (std::range_error& e) {
    REQUIRE(true);
  }
}

TEST_CASE("provoking exceptions in peek method") {
  List<int> list;
  try {
    list.peek(0);
    REQUIRE(false);
  } catch (std::range_error& e) {
    REQUIRE(true);
  }
  try {
    list.peek(2);
    REQUIRE(false);
  } catch (std::range_error& e) {
    REQUIRE(true);
  }
}

TEST_CASE("provoking iterator exceptions") {
  List<int> list;
  list.insert(0, 0);
  list.insert(1, 1);
  try {
    auto i = list.begin();
    --i;
    --i;
    REQUIRE(false);
  } catch (std::range_error& e){
    REQUIRE(true);
  }
  try {
    auto i = list.end();
    ++i;
    REQUIRE(false);
  } catch (std::range_error& e){
    REQUIRE(true);
  }
}
