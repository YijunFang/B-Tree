#include <algorithm>
#include <iostream>
#include <iterator>

#include "btree.h"

// void foo(const btree<int> &b) {
//   btree<int>::iterator iter = b.begin();
//   btree<int>::iterator ends = b.end();
  // std::cout << *iter << " " << *ends << std::endl;
  // std::copy(iter, ends, std::ostream_iterator<int>(std::cout, " "));
//  std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));
//   std::cout << std::endl;
// }

template <typename T> void display(T &c) {
  std::cout << "Iterating over tree top: ";
  // typename T::iterator i = c.begin();
  for (typename T::iterator i = c.begin(); i != c.end(); ++i) 
  // or for (auto i = c.begin(); i != c.end(); ++i)
    std::cout << *i << " "; 
  std::cout << std::endl;
}

// template <typename T> void printIterator(T &c) {
//   std::cout << "element = "<< *c << std::endl;
// }


int main(int argc, char* argv[]) {
  btree<int> b(3);

  // printf("insert 1\n");
  b.insert(1);
  display(b);

  b.insert(10);
  display(b);

  // printf("insert 8\n");
  b.insert(8);
  display(b);
  
  // // printf("insert 9\n");
  b.insert(9);
  display(b);

  // // printf("insert 4\n");
  b.insert(4);
  display(b);

  // // printf("insert 5\n");
  b.insert(5);
  display(b);

  // // printf("insert 14\n");
  b.insert(14);
  display(b);

  // // printf("insert 0\n");
  auto pair = b.insert(0);
  display(b);

 // std::cout << "pointee point to element at index"<< i.getIndex()<< std::endl;
  std::cout << "element = "<< *pair.first;
  std::cout << ", insert = " << pair.second << '\n';

//  btree<int> c;
//  c = b;

  // for (btree<int>::iterator iter = b.begin(); iter != b.end(); ++iter)
  //   std::cout << *iter << std::endl;
//  cout << std::endl;
//  for (btree<int>::iterator iter = c.begin(); iter != c.end(); ++iter)
//    std::cout << *iter << std::endl;
  // foo(b);
  //delete [] argv;
  return 0;
}
