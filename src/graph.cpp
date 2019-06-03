//
// Created by rafab on 6/2/2019.
//

#include "../include/graph.h"
Graph::Graph() {

    parser_.PopulateActors(actors_, actor_);
    actor_[0].second->push_back("Stuff goes here");
    actor_[0].second->push_back("Stuff goes here");
    actor_[0].second->push_back("Stuff goes here");
//    actor_[actors_.at("nm0000102")].second->push_back("hello world");
//  parser_.PopulateCast(cast_);
//    parser_.PopulateTitles(movies_);

}
Graph::~Graph() {

}
Graph::Graph(const Graph &other) {

}
Graph &Graph::operator=(const Graph &other) {
  //  return <#initializer#>;
}

void Graph::GetActorName(std::string &nconst)
{
  if(actors_.count(nconst))
    std::cout<<"Actor found "<<actors_[nconst]<<'\n';
  else
    std::cout<<"Actor not found.\n";
}

void Graph::GetCast(std::string &tconst)
{
  if(cast_.count(tconst))
  {
    std::pair <std::multimap<std::string,std::string>::iterator, std::multimap<std::string,std::string>::iterator> ret;
    ret = cast_.equal_range(tconst);
    std::cout << tconst << " =>";
    for (std::multimap<std::string,std::string>::iterator it=ret.first; it!=ret.second; ++it)
      std::cout << ' ' << it->second;
    std::cout << '\n';
  }
  else
    std::cout<<"Movie or cast not found.\n";
}

void Graph::GetMovieName(std::string &tconst)
{
  if(movies_.count(tconst))
    std::cout<<"Movie found "<<movies_[tconst]<<'\n';
  else
    std::cout<<"Movie not found.\n";
}

void Graph::BreadthFirstSearch(std::string &nconst) {
//  std::queue<std::string>
}
