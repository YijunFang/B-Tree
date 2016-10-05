#include <algorithm>
#include <iostream>
#include <iterator>

#include "btree.h"

void foo(const btree<int> &b) {
  std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
}

template <typename T> void display(T &c) {
  std::cout << "Iterating over tree top: ";
  for (typename T::iterator i = c.begin();i != c.end(); ++i)
    std::cout << *i << " "; 
  std::cout << std::endl;
}


int main(int argc, char* argv[]) {
  btree<int> b(3);

  printf("insert 1\n");
  b.insert(1);
  // display(b);

  b.insert(10);
  // display(b);

  printf("insert 8\n");
  b.insert(8);
  // display(b);

  printf("insert 9\n");
  b.insert(9);
  // display(b);

  printf("insert 4\n");
  b.insert(4);
  // display(b);

  printf("insert 5\n");
  b.insert(5);
  // display(b);

  printf("insert 14\n");
  b.insert(14);
  // display(b);

  printf("insert 0\n");
  b.insert(0);

  // std::cout << "pointee point to element at index"<< i.getIndex()<< std::endl;
  // std::cout << "element = "<< *pair.first;
  // std::cout << ", insert = " << pair.second << '\n';

  std::cout <<"find 10: "<< *b.find(10)<< std::endl;

  printf("copy constructor\n");
  btree<int> c = b;

  // //  c = b;
  printf("insert 20\n");
  b.insert(20);
  printf("insert 50\n");
  b.insert(50);
  printf("insert 22\n");
  b.insert(22);
  printf("insert 44\n");
  b.insert(44);
  printf("insert 55\n");
  b.insert(55);
  printf("insert 55\n");
  b.insert(55);
  // display(b);

  printf("insert 77\n");
  b.insert(77);

  b.insert(18);

  b.insert(52);
  b.insert(-1);
  b.insert(56);
  b.insert(100);
  c.insert(88);
  display(b);
  printf("copy assignment\n");
  btree<int> d;
  d = b;

  // display(b);

  // display(c);

  // display(d);

  printf("move constructor\n");
  btree<int> e = std::move(b);
  // display(b);
  // display(e);

  printf("move assignment\n");
  btree<int> f;
  f = std::move(e);

  std::cout << b << std::endl;

  std::cout << c << std::endl;

  std::cout << d << std::endl;

  std::cout << e << std::endl;

  std::cout << f << std::endl;

  display(b);
  display(c);
  display(d);
  display(e);
  display(f);


  foo(b);
  // delete [] argv;
  return 0;
}
