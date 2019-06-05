/**
 * @author      Rafael Betita & Ara Mico Segismundo
 * @modified    06-02-2019
 */

#ifndef BACONS_LAW_INCLUDE_GRAPH_H_
#define BACONS_LAW_INCLUDE_GRAPH_H_

#include "parser.h"
#include "actorcrew.h"

class Graph {

 public:
  Graph();
  ~Graph();
  Graph(const Graph& other);
  Graph& operator=(const Graph& other);

  void GetActorName(std::string &nconst);
  void GetCast(std::string &tconst);
  void GetMovieName(std::string &tconst);
  void BreadthFirstSearch(std::string &nconst);

 private:
  Parser parser_;
//  std::vector<actor_pair> actor_;
  std::vector<Actor*> actorMovies_; // [0]=name [1]=movie tconst
  std::vector<std::string*> movieCrew_; //
  std::map<std::string, int> mIndex_; // Movie ID -> Index
  std::map<std::string, int> aIndex_; // Actor ID -> Index
  std::map<std::string, std::string> movies_; // Movie ID -> Movie Title
//  std::multimap <std::string, std::string> cast_; // Movie ID -> Actors
//  std::vector<std::string> movies_;
//  std::vector<std::string> actors_;

};

#endif //BACONS_LAW_INCLUDE_GRAPH_H_
