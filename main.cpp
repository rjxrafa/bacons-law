#include "include/menu.h"
#include "include/avl.h"

using namespace std;

int main() {
//    Menu sixDegrees;
//
//    sixDegrees.Run();
  avl::BinaryTree<int> a;
  a << 5;
  a << 3;
  a << 4;
  a << 2;
  a << 1;

  std::cout << a;

  std::cout << a[5] << std::endl;

  cs8::Queue<int> b;
  b << 1;
  b << 2;
  cout<<b;

  return 0;
}
