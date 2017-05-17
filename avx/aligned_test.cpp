#include<cstdlib>
#include<cstdio>

using namespace std;

int main(void){
  int *p1 = (int *)malloc(10*sizeof(*p1));
  printf("default-aligned addr: %p\n", p1);
  free(p1);

  int *p2 = (int *)aligned_alloc(256*16, 10*sizeof(*p2));
  printf("        aligned addr: %p\n", p2);
  free(p2);

}
