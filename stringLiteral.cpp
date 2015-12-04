#include<iostream>
#include<string>

using namespace std;

#define DEBUG_STRING_LITERAL NDEBUG

namespace {

#if DEBUG_STRING_LITERAL
  using DebugStringLiteral = string;
#endif

#if DEBUG_STRING_LITERAL
  DebugStringLiteral STRING{"A hello from Samar"s};
#endif
}

int main(){

#if DEBUG_STRING_LITERAL
  cout << STRING << endl;
#endif
  return 0;
}
