#include "../include/graph.h"

Graph::Graph() {

    parser_.PopulateActors(aIndex_, actorMovies_);
    parser_.PopulateCast(aIndex_, actorMovies_, movieCrew_, mIndex_);
  //  parser_.PopulateTitles(movies_);

}
Graph::~Graph() {
    actorMovies_.clear();
    movieCrew_.clear();
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
//nm0000102    Kevin Bacon    1958
    cs8::Queue<int> sixDegrees;
    int actor;

    for(unsigned int i = 0; i < actorMovies_.size(); ++i)
    {
        actorMovies_[i]->visited = false;
    }
    //name to nconst
    //nconst to fakeptr
    sixDegrees.enqueue(actorMovies_[aIndex_[nconst]]->actorID);

    while(!sixDegrees.empty())
    {
        sixDegrees >> actor;

        if(!actorMovies_[aIndex_[nconst]]->visited)
        {
            actorMovies_[aIndex_[nconst]]->visited = true;
            //search each of their movie
            for(unsigned int j = 0; j < actorMovies_[aIndex_[nconst]]->movies.size(); ++j)
            {
                //tconst = actorMovies_[aIndex_[nconst]]->movies[j];
                for(unsigned int i = 0; i < movieCrew_[mIndex_["tconst"]]->actors.size(); ++i)
                {
                    if( movieCrew_[mIndex_["tconst"]]->actors[i] == 102)
                    {
                        //kevin bacon found yay
                        return;
                    }
                    else
                        std::cout<<'n';
                        //mark movie visited queue those actors
                }
            }

        }
    }
//    1  procedure BFS(G,start_v):
//    2      let Q be a queue
//    3      label start_v as discovered
//    4      Q.enqueue(start_v)
//    5      while Q is not empty
//    6          v = Q.dequeue()
//    7          if v is the goal:
//    8              return v
//    9          for all edges from v to w in G.adjacentEdges(v) do
//    10             if w is not labeled as discovered:
//    11                 label w as discovered
//    12                 w.parent = v
//    13                 Q.enqueue(w)
//   BFS pseudocode
//    Set all nodes to "not visited";

//   q = new Queue();

//   q.enqueue(initial node);

//   while ( q ≠ empty ) do
//   {
//      x = q.dequeue();

//      if ( x has not been visited )
//      {
//         visited[x] = true;         // Visit node x !

//         for ( every edge (x, y)  /* we are using all edges ! */ )
//            if ( y has not been visited )
//	       q.enqueue(y);       // Use the edge (x,y) !!!
//      }
//   }
}
