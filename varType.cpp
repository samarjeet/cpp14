#include<iostream>
#include<typeinfo>

using namespace std;
class MyClass {
};

int main(){
  auto variable = 1;
  auto classVar = MyClass();

  cout << "Type of the variable is : " << typeid(variable).name() << endl;   
  cout << "Type of the variable is : " << typeid(classVar).name() << endl;   
  
  return 0;
}
