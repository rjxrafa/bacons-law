/**
 * This is a graph class that does Breadth First Search
 * using actors as vertices and movies as edges
 *
 * @authors     Ara Mico Segismundo & Rafael Betita
 * @modified    2019-06-10
 */

#ifndef BACONS_LAW_INCLUDE_GRAPH_H_
#define BACONS_LAW_INCLUDE_GRAPH_H_

#include "parser.h"
#include "actorcrew.h"
#include "myqueue.h"
#include "map.h"
//#include "algorithm"

class Graph {
public:
    Graph();
    ~Graph();

    void BreadthFirstSearch(int &actorNameFrom, int &actorNameTo);
    bool GraphGetInput(int &nconst, std::string &&question);

private:
    Parser parser_;
    std::vector<Actor*> actorMovies_; // Actor's info
    std::vector<Crew*> movieCrew_; // Movie's crew info
    cs8::Map<std::string, std::vector<int>> actor_to_id_; //Actor Name -> Actor ID(if duplicate will pushback other ids with same name)
    cs8::Map<int, int> movieIndex_; // Movie ID -> Index
    cs8::Map<int, int> actorIndex_; // Actor ID -> Index
    cs8::Map<int, std::string> movies_; // Movie ID -> Movie Title
};

#endif //BACONS_LAW_INCLUDE_GRAPH_H_
