#include<boost/lambda/lambda.hpp>
#include<iostream>
#include<iterator>
#include<algorithm>

using namespace std;
using namespace boost::lambda;


int main(){

  typedef istream_iterator<int> in;

  for_each(
    in(cin), in(), cout << (_1 * 3) << " " 
  );
}
