#include<iostream>

template <typename T>
struct Test{
    Test() = default;
    explicit Test(const T& arg) :m_member(arg) {}
    T m_member{};
};

int main() {
    Test<int> t1;
    int v2 = 34;
    Test<int&> t2(v2);
    return 0;
}
