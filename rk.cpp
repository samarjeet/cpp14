#include<iostream>
#include<vector>


class Euler {
private :
  double delT;
  std::vector<double> c;
public :

  Euler() {
    delT = 1.0;
    c = {1, delT/2, delT/2, delT};
  }
  std::vector<double> f(std::vector<double> x, double t) {
    std::vector<double> v;
    return v;
  }

};

int main() {

  Euler e; 
  return 0;
}
