#include<iostream>
#include<algorithm>
#include<array>
#include<cstdint>
#include<typeinfo>
#include<vector>

using MyVector = std::vector<uint32_t>;

int main(){

  using MyArray = std::array<uint32_t, 5>;
  MyArray myArray{1,2,3,4,5};
  MyVector myVector;

  auto myClosure = [&myVector](auto&& number){
    //std::cout << number << std::endl;
    myVector.push_back(number);  
  };

  std::cout << typeid(myClosure).name() << std::endl;

  std::for_each(myArray.cbegin(),
    myArray.cend(), myClosure
  );

  std::for_each(myVector.cbegin(),
    myVector.cend(),[](auto&& number){
      std::cout << number << std::endl;
    });
  return 0;
}
