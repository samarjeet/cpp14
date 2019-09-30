#include<stdio.h>
#include <iostream>

/*
 *
 * An lvalue is an expression that refers to a memory location and allows us to 
 * take the address of that memory location via the & operator. 
 *
 * An rvalue is an expression that is not an lvalue.
 *
 *
 * */

template <typename T>
void ptype(T& t) {

  std::cout << "l-value reference" ;
}
template <typename T>
void ptype(T&& t) {

  std::cout << "r-value reference" ;
}

int x;
int& getRef () {
  return x;
}

int main(){
  x=4;
  getRef() = 6;
  printf("Value : %d\n", getRef());

  int y = 10;
  std::cout << "&y :  " ;
  ptype(&y);
  std::cout << std::endl;
  //printf("Address : %d\n", &getRef());
  return 0;
}
