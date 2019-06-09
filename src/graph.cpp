#include "../include/graph.h"

Graph::Graph() {

    parser_.PopulateActors(actor_to_id_,actorIndex_, actorMovies_);
    parser_.PopulateCast(actorIndex_, actorMovies_, movieCrew_, movieIndex_);
    parser_.PopulateTitles(movies_);

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

void Graph::GetActorName(int &nconst)
{
  if(actorIndex_.count(nconst))
  {
//    std::cout<<"Actor found "<<actorMovies_[aIndex_[nconst]][0]<<'\n';
//    std::cout<<"Movies found "<<actorMovies_[aIndex_[nconst]][1]<<'\n';
  }
  else
    std::cout<<"Actor not found.\n";
}

void Graph::GetCast(int &tconst)
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

void Graph::GetMovieName(int &tconst)
{
  if(movies_.count(tconst))
    std::cout<<"Movie found "<<movies_[tconst]<<'\n';
  else
    std::cout<<"Movie not found.\n";
}

void Graph::BreadthFirstSearch(std::string &actorName) {
//  std::queue<std::string>
//nm0000102    Kevin Bacon    1958 nm0000102 is 102 in int
    cs8::Queue<int> sixDegrees;
    int origin, actor, index;

    //Resetting flags
    for(unsigned int i = 0; i < actorMovies_.size(); ++i)
    {
        actorMovies_[i]->visited = false;
        actorMovies_[i]->parent = nullptr;
    }
    for(unsigned int i = 0; i < movieCrew_.size(); ++i)
    {
        movieCrew_[i]->visited = false;
    }


    //name to nconst
    //nconst to fakeptr
    if(!actor_to_id_.count(actorName))
    {
        std::cout<<"Actor name not found.\n";
        return;
    }

    if(actor_to_id_.at(actorName).size() == 1)
    {
        sixDegrees.enqueue(actorMovies_[actorIndex_[actor_to_id_[actorName][0]]]->actorID);
        origin = actorMovies_[actorIndex_[actor_to_id_[actorName][0]]]->actorID;
    }
    else
    {
        std::cout<<"Duplicate actors, which actor?\n";
        for(size_t i = 0; i < actor_to_id_.at(actorName).size(); ++i)
        {
            std::cout<<i<<':';
            if(actorMovies_[actorIndex_[actor_to_id_[actorName][i]]]->famousMovies.size() != 0)
            {
                for(size_t j = 0; j < actorMovies_[actorIndex_[actor_to_id_[actorName][i]]]->famousMovies.size(); ++j)
                {
                    if(j == actorMovies_[actorIndex_[actor_to_id_[actorName][i]]]->famousMovies.size() - 1)
                    {
                        if(movies_.count(actorMovies_[actorIndex_[actor_to_id_[actorName][i]]]->famousMovies[j]))
                            std::cout<<movies_[actorMovies_[actorIndex_[actor_to_id_[actorName][i]]]->famousMovies[j]];
                        else
                            std::cout<<"Movie not found or not in US";
                    }
                    else
                        if(movies_.count(actorMovies_[actorIndex_[actor_to_id_[actorName][i]]]->famousMovies[j]))
                            std::cout<<movies_[actorMovies_[actorIndex_[actor_to_id_[actorName][i]]]->famousMovies[j]]<<','<<' ';
                        else
                            std::cout<<"Movie not found or not in US"<<','<<' ';
                }
            }
            else
                std::cout<<"No movies";

            std::cout<<'\n';
        }
        std::cin >> index;
        std::cin.ignore(256, '\n');
        actor = actor_to_id_[actorName][index];
        origin = actor;
        sixDegrees.enqueue(actor);
    }

    int movieIndex, actorIndex, baconNumber = 0;

    while(!sixDegrees.empty())
    {
        actor = sixDegrees.dequeue();
        //if the person has not been visited
        if(actorMovies_[actorIndex_[actor]]->visited == false) //actorMovies_[actorIndex_[actor]] actor is the id that is put in actorIndex_ to get a index to get the information of an actor in actorMovies_ vector
        {
            //set to being visited
            actorMovies_[actorIndex_[actor]]->visited = true;
            //Go thru their movies
            for(int i = 0; i < actorMovies_[actorIndex_[actor]]->movies.size(); ++i)
            {
                movieIndex = movieIndex_[actorMovies_[actorIndex_[actor]]->movies[i]];
                //actorMovies_[actorIndex_[actor]]->movies[i]] returns a tconst that you put in movie index
                if(movieCrew_[movieIndex]->visited == false)
                {
                    //set movie to being visited true so reprocessing does have to be done
                    movieCrew_[movieIndex]->visited = true;

                    //check the actors in the movie
                    for(int j = 0; j < movieCrew_[movieIndex]->actors.size(); ++j)
                    {

                        actorIndex = actorIndex_[movieCrew_[movieIndex]->actors[j]];
                        //102 is kevin bacons number
                        if(movieCrew_[movieIndex]->actors[j] == 102)
                        {
                            if(actorMovies_[actorIndex] != actorMovies_[actorIndex_[actor]])
                                actorMovies_[actorIndex_[102]]->parent = actorMovies_[actorIndex_[actor]];
                            Actor *temp = actorMovies_[actorIndex_[102]];
                            std::cout<<temp->actorID<<" <- ";
                            for(temp = temp->parent ; temp != nullptr; temp = temp->parent)
                            {
                                if(temp->parent == nullptr)
                                    std::cout<<temp->actorID;
                                else
                                    std::cout<<temp->actorID<<" <- ";
                                ++baconNumber;
                            }
                            std::cout<<'\n';
                            std::cout<<actorName<<"'s Bacon number is "<<baconNumber<<'\n';
                            //return the origins bacon number
                            return;
                        }
                        else
                        {
                            //Enqueue Actor that isnt kevin bacon
                            if(actorMovies_[actorIndex] != actorMovies_[actorIndex_[actor]])
                                actorMovies_[actorIndex]->parent = actorMovies_[actorIndex_[actor]];
                            sixDegrees.enqueue(movieCrew_[movieIndex]->actors[j]);
                        }
                    }
                }
            }
        }
    }
}
