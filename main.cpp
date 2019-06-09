#include "include/menu.h"
#include "include/map.h"

using namespace std;

int main() {

  cs008::Map<int, std::string> actors;

  actors.Insert(102, "Kevin Bacon");
  actors.Insert(103, "Kevin Ham");
  actors.Insert(104, "Kevin IceCream");
  actors.Insert(105, "Kevin Pork");
  actors.Insert(106, "Kevin Butter");
  std::cout << actors << std::endl << std::endl << std::endl;

  cs008::Map<int, std::string> movies;
  movies.Insert(231, "The Baconator");
  movies.Insert(131, "Ham 2");
  movies.Insert(9, "Shrek 3D");
  movies.Insert(38, "Sharknado");
  movies.Insert(2222, "Asian College Cuties");
  movies.Insert(2222, "Asian College Cuties");

  cs008::Map<int, std::string> test;
  test.Insert(123, "Test movie");

  movies = test;

  std::cout << movies << std::endl;

  movies.Remove(9);

  std::cout << movies << std::endl;

  std::cout << movies[2222];
//  std::cout << a;

//  std::cout << a[5] << std::endl;

//  cs8::Queue<int> b;
//  b << 1;
//  b << 2;
//  cout<<b;

  return 0;
}
