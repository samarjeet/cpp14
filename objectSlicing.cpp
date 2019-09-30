#include <iostream>
#include <memory>
#include <vector>
/*
 * Testing object slicing in this test case.
 * I want to have a vector of Base Type, where the elements could be any of the derived types.
 *
 * However, due to object slicing, the functions of the derived class are not accessible.
 *
 * Solution : use shared_ptr and static_pointer_cast it to the derived class.
 */

class Base {
private:
  int numBase;

public:
  Base(int numBase) : numBase(numBase) {}
  int getNumBase() const { return numBase; }
};

class Derived : public Base {
private:
  int numDerived;

public:
  Derived(int num) : numDerived(num), Base(num - 1) {}
  int getNumDerived() const { return numDerived; }
};

int main(int argc, char **argv) {

  std::vector<std::unique_ptr<Base>> vec;
  vec.push_back(std::make_unique<Derived>(12));
  std::cout << "Base " << vec[0]->getNumBase() << "\n";
  //std::cout << "Derived " << static_cast<std::unique_ptr<Derived>>(vec[0])->getNumDerived() << "\n";

  std::vector<std::shared_ptr<Base>> sharedVec;
  sharedVec.push_back(std::make_shared<Derived>(12));
  std::cout << "Base " << sharedVec[0]->getNumBase() << "\n";
  std::cout << "Derived " << std::static_pointer_cast<Derived>(sharedVec[0])->getNumDerived() << "\n";
  return 0;
}
