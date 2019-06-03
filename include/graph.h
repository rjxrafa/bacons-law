/**
 * @author      Rafael Betita & Ara Mico Segismundo
 * @modified    06-02-2019
 */

#ifndef BACONS_LAW_INCLUDE_GRAPH_H_
#define BACONS_LAW_INCLUDE_GRAPH_H_

#include "mylib.h"
#include "parser.h"

class Graph {

 public:
  Graph();
  ~Graph();
  Graph(const Graph& other);
  Graph& operator=(const Graph& other);

  void GetActorName(std::string &nconst);
  void GetCast(std::string &tconst);
  void GetMovieName(std::string &tconst);

 private:
  Parser parser_;
  std::map<std::string, std::string> actors_; // Actor ID -> Actor Name
  std::map<std::string, std::string> movies_; // Movie ID -> Movie Title
  std::multimap <std::string, std::string> cast_;
//  std::vector<std::string> movies_;
//  std::vector<std::string> actors_;

};

#endif //BACONS_LAW_INCLUDE_GRAPH_H_
