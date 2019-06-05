#include "../include/graph.h"

Graph::Graph() {

    parser_.PopulateActors(aIndex_, actorMovies_);
    parser_.PopulateCast(aIndex_, actorMovies_, movieCrew_, mIndex_);
  //  parser_.PopulateTitles(movies_);

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
  if(aIndex_.count(nconst))
  {
//    std::cout<<"Actor found "<<actorMovies_[aIndex_[nconst]][0]<<'\n';
//    std::cout<<"Movies found "<<actorMovies_[aIndex_[nconst]][1]<<'\n';
  }
  else
    std::cout<<"Actor not found.\n";
}

void Graph::GetCast(std::string &tconst)
{
//  if(cast_.count(tconst))
//  {
//    std::pair <std::multimap<std::string,std::string>::iterator, std::multimap<std::string,std::string>::iterator> ret;
//    ret = cast_.equal_range(tconst);
//    std::cout << tconst << " =>";
//    for (std::multimap<std::string,std::string>::iterator it=ret.first; it!=ret.second; ++it)
//      std::cout << ' ' << it->second;
//    std::cout << '\n';
//  }
//  else
//    std::cout<<"Movie or cast not found.\n";
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
