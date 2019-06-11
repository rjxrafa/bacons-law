/**
 * This is a graph class that does Breadth First Search
 *
 * @author      Ara Mico Segismundo & Rafael Betita
 * @modified    2019-06-10
 */

#ifndef BACONS_LAW_INCLUDE_GRAPH_H_
#define BACONS_LAW_INCLUDE_GRAPH_H_

#include "parser.h"
#include "actorcrew.h"
#include "myqueue.h"
#include "avl.h"

class Graph {

 public:
  Graph();
  ~Graph();
  Graph(const Graph& other);
  Graph& operator=(const Graph& other);

  void GetActorName(int &nconst);
  void GetCast(int &tconst);
  void GetMovieName(int &tconst);
  void BreadthFirstSearch(int &actorNameFrom, int &actorNameTo);
  bool GraphGetInput(int &nconst, std::string &&question);

 private:
  Parser parser_;
  std::vector<Actor*> actorMovies_; // [0]=name [1]=movie tconst
  std::vector<Crew*> movieCrew_; //
  cs8::Map<std::string, std::vector<int>> actor_to_id_; //Actor Name -> Actor ID(if duplicate will pushback other ids with same name)
  cs8::Map<int, int> movieIndex_; // Movie ID -> Index
  cs8::Map<int, int> actorIndex_; // Actor ID -> Index
  cs8::Map<int, std::string> movies_; // Movie ID -> Movie Title

};

#endif //BACONS_LAW_INCLUDE_GRAPH_H_
