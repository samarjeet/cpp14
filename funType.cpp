#include<iostream>
#include<typeinfo>

using namespace std;

auto returnFromFun(int para)  -> int 
{
  return para;
}
int main(){

  auto var = returnFromFun(1);
  cout << "Type of the function is  : " << typeid(var).name() << endl;
  return 0;
}
