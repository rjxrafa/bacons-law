#include "include/menu.h"
#include "include/map.h"
#include "include/multimap.h"

using namespace std;

int main() {

  cs8::Multimap<int, std::string> movies;
  movies.Insert(123, "Kevin Bacon");
  movies.Insert(123, "Kevin Bacon Jr.");
  movies.Insert(123, "Kevin Bacon Sr.");
  movies.Insert(123, "Kevin Bacon III");

  movies.Insert(20123, "Rafa");
//  movies.Insert(20123, "Rafa Jr.");
//  movies.Insert(20123, "Rafa Sr.");

  movies.Insert(11, "Mico");
//  movies.Insert(11, "Ara Segismundo");

  movies.Insert(33, "Shrek");

//  cs8::Map<int, std::string> test;
//  test = movies;

//  test.Remove(33);
  movies.Remove(123, "Kevin Bacon Jr.");

  std::cout << movies << std::endl;
  std::cout << boolalpha << movies.Remove(123123);
  std::cout << movies.Count(123);

  return 0;
}
