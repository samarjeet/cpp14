#include<iostream>
#include<typeinfo>

// pipe the output to 'c++filt -t' to get the types in human-readable format

using namespace std;

template<typename T>
auto fromFunction(T para) //-> decltype(para)  ** need to append this if you are working with c++11
{
  
  return para;
}

auto returnFromFun(int para)  -> int 
{
  return para;
}
int main(){

  auto var = returnFromFun(1);
  cout << "Type of the function is  : " << typeid(var).name() << endl;

  auto var2 = fromFunction(1);
  cout << "Type of the function is  : " << typeid(var2).name() << endl;
  return 0;
}
