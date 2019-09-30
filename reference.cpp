#include<iostream>

//template <typename Tpara>
//void f(Tpara& p) {}

template <typename Tpara>
void f( Tpara&& p) {
  //std::cout << p << "\n";
}


int main() {

  int i = 5;
  double k = 5.0;
  //double& j = k;
  int& j = i;
  f(i);
  f(j);
  f(std::move(i));
  f(std::move(j));
  f(4.0);
  return 0;
}
