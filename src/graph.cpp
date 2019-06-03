//
// Created by rafab on 6/2/2019.
//

#include "../include/graph.h"
Graph::Graph() {

//    parser_.PopulateActors(actors_);
    parser_.PopulateCast(cast_);
    parser_.PopulateTitles(movies_);

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

}
void Graph::GetMovieName(std::string &tconst)
{
    if(movies_.count(tconst))
        std::cout<<"Movie found "<<movies_[tconst]<<'\n';
    else
        std::cout<<"Movie not found.\n";
}
