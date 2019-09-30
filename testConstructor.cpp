/*
 * To test default constructors
 */

#include<iostream>

class Component{
private :
  int n;
public :
  Component(){
    n=5;
  }
  Component(int nIn){
    n = nIn;
  }
};

class Product {
private :
  Component comp;
public :
  Product(int n){
    std::cout << "Product created\n";
  }
};

int main(){

  Product prod(5);  
  return 0;
}
