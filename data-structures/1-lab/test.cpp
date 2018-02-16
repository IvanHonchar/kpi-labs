#include <iostream>
#include "linked-list.h"

using namespace std;

int main() {
  List<char> list;

  char array[10] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
  for (int i = 0; i < 10; i++) {
    list.insert(array[i], i); // insert 10 elements into the list
  }

  list.insert('1', 0);    // insert '1' at the begin of the list
  list.insert('2', 11);   // insert '2' at the end of the list
  list.insert('3', 6);    // insert '3' after 6th element of the list

  try {                   // try to insert '4' after 20th element of list
    list.insert('4', 20); // but we know that there are only 13 elements
  }                       // so it will throw an error
  catch(const char* err) {
    cout << err << endl;  // catch error and log it
  }

  for (Node<char>* cur = list.begin();; cur = cur->next) {  // log list
    if (cur != NULL) cout << cur->data << ' ';              // in direct order
    if (cur == list.end()) break;
  }
  cout << endl;

  for (Node<char>* cur = list.end();; cur = cur->prev) {    // log list
    if (cur != NULL) cout << cur->data << ' ';              // in reverse order
    if (cur == list.begin()) break;
  }
  cout << endl;
}
