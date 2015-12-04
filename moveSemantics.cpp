#include<iostream>

using namespace std;

class MyClass{
  private :
    static int s_Counter;
    int* m_Member{ &s_Counter }; //l-value    
  public :

    MyClass(){
      ++(*m_Member);
      cout << "Constructing : " << s_Counter << endl;
    }

    ~MyClass(){
      --(*m_Member);
      m_Member = nullptr;
      cout << "Destrucitng : " << s_Counter << endl;
    }
    
    // Copy constructor
    MyClass(const MyClass& rhs):m_Member{rhs.m_Member}{
      ++(*m_Member);
      cout << "Copying : " << s_Counter << endl;
    }

    MyClass(MyClass&& rhs):m_Member{rhs.m_Member}{
      ++(*m_Member);
      cout << "Moving : " << s_Counter << endl;
    }  
    
    int getValue(){
      return *m_Member;
    }
};

int MyClass::s_Counter{0};

MyClass copyMyClass(MyClass para){
  return para;
}

int main(){
  auto obj1 = MyClass();

  {
    auto obj2 = MyClass();
  }

  auto obj3 = MyClass();
  auto obj4 = copyMyClass(obj3);

  return 0;
}
