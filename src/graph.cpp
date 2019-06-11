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

  return *this;
}

void Graph::GetActorName(int &nconst)
{
  if(actorIndex_.Count(nconst))
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
  if(movies_.Count(tconst))
    std::cout<<"Movie found "<<movies_[tconst]<<'\n';
  else
    std::cout<<"Movie not found.\n";
}

void Graph::BreadthFirstSearch(int &actorNameFrom, int &actorNameTo) {
//  std::queue<std::string>
//nm0000102    Kevin Bacon    1958 nm0000102 is 102 in int
    cs8::Queue<int> sixDegrees;
    int origin, actor, index;

    //Resetting flags
    for(unsigned int i = 0; i < actorMovies_.size(); ++i)
    {
        actorMovies_[i]->visited = false;
        actorMovies_[i]->parent = nullptr;
        actorMovies_[i]->parentM = nullptr;
    }
    for(unsigned int i = 0; i < movieCrew_.size(); ++i)
    {
        movieCrew_[i]->visited = false;
    }

    origin = actorNameFrom;
    sixDegrees.enqueue(actorNameFrom);

    int movieIndex, actorIndex, baconNumber = 0;

    if(actorNameFrom == actorNameTo)
    {
        std::cout<<actorMovies_[actorIndex_[actorNameFrom]]->name<<" Bacon Number is 0.\n";
        return;
    }

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
                        if(movieCrew_[movieIndex]->actors[j] == actorNameTo)
                        {
                            if(actorMovies_[actorIndex] != actorMovies_[actorIndex_[actor]])
                            {
                                actorMovies_[actorIndex_[actorNameTo]]->parent = actorMovies_[actorIndex_[actor]];
                                actorMovies_[actorIndex_[actorNameTo]]->parentM = movieCrew_[movieIndex];
                            }

                            Actor *actorTemp = actorMovies_[actorIndex_[actorNameTo]];
                            std::cout<<"------------------------------\n";
                            if(movies_.Count(actorTemp->parentM->movieID) == 1)
                            std::cout<<actorTemp->name<<"\n IN \n"<<movies_[actorTemp->parentM->movieID] <<"\n WITH \n";
                            else
                                std::cout<<actorTemp->name<<"\n IN \n"<<"Movie not found" <<"\n WITH \n";
                            for(actorTemp = actorTemp->parent ; actorTemp != nullptr; actorTemp = actorTemp->parent)
                            {
                                if(actorTemp->parent == nullptr)
                                    std::cout<<actorTemp->name;
                                else
                                {
                                    if(movies_.Count(actorTemp->parentM->movieID) == 1)
                                    std::cout<<actorTemp->name<<"\n IN \n"<<movies_[actorTemp->parentM->movieID]<< "\n WITH \n";
                                    else
                                        std::cout<<actorTemp->name<<"\n IN \n"<<"Movie not found" <<"\n WITH \n";
                                }
                                ++baconNumber;
                            }
                            std::cout<<'\n';
                            std::cout<<actorMovies_[actorIndex_[actorNameFrom]]->name<<"'s Bacon number is "<<baconNumber<<'\n';
                            std::cout<<"------------------------------\n";
                            return;
                        }
                        else
                        {
                            //Enqueue Actor that isnt kevin bacon
                            if(actorMovies_[actorIndex] != actorMovies_[actorIndex_[actor]])
                            {
                                actorMovies_[actorIndex]->parent = actorMovies_[actorIndex_[actor]];
                                actorMovies_[actorIndex]->parentM = movieCrew_[movieIndex];
                            }

                            sixDegrees.enqueue(movieCrew_[movieIndex]->actors[j]);
                        }
                    }
                }
            }
        }
    }

    std::cout<<"Chosen person is either not an actor, or does not have enough significance to be in IMDB's title principle file.\n";
}

bool Graph::GraphGetInput(int &nconst, std::string &&question)
{
    bool found = false, done = true;
    int index = 0, range = 0;
    size_t notInt;
    std::string s, s1;
    printf("%s\n", question.c_str());

    while(!found)
    {
        getline(std::cin, s);
        if(s.empty())
            exit(0);

        if(!actor_to_id_.Count(s))
        {
            std::cout<<"Actor name not found please re-enter a name.\n";
        }
        else
            found = true;
    }

    if(actor_to_id_[s].size() == 1)
    {
        nconst = actorMovies_[actorIndex_[actor_to_id_[s][0]]]->actorID;
//        sixDegrees.enqueue(actorMovies_[actorIndex_[actor_to_id_[actorNameFrom][0]]]->actorID);
//        origin = actorMovies_[actorIndex_[actor_to_id_[actorNameFrom][0]]]->actorID;
        return true;
    }
    else
    {
        std::cout<<"Duplicate actors, which actor?\n";
        for(size_t i = 0; i < actor_to_id_[s].size(); ++i)
        {
            std::cout<<i<<':';
            if(actorMovies_[actorIndex_[actor_to_id_[s][i]]]->famousMovies.size() != 0)
            {
                for(size_t j = 0; j < actorMovies_[actorIndex_[actor_to_id_[s][i]]]->famousMovies.size(); ++j)
                {
                    if(j == actorMovies_[actorIndex_[actor_to_id_[s][i]]]->famousMovies.size() - 1)
                    {
                        if(movies_.Count(actorMovies_[actorIndex_[actor_to_id_[s][i]]]->famousMovies[j]))
                            std::cout<<movies_[actorMovies_[actorIndex_[actor_to_id_[s][i]]]->famousMovies[j]];
                        else
                            std::cout<<"Movie not found or not in US";
                    }
                    else
                        if(movies_.Count(actorMovies_[actorIndex_[actor_to_id_[s][i]]]->famousMovies[j]))
                            std::cout<<movies_[actorMovies_[actorIndex_[actor_to_id_[s][i]]]->famousMovies[j]]<<','<<' ';
                        else
                            std::cout<<"Movie not found or not in US"<<','<<' ';
                }
            }
            else
                std::cout<<"No movies";

            std::cout<<'\n';
            range = i;
        }

        do
        {
            if(GetInput(s1,"Index:"))
            {
                notInt = s1.find_first_not_of("0123456789");
                if(notInt!=std::string::npos)
                {
                    std::cout<<"Invalid input. Please re-enter.\n";
                    done = true;
                }
                else
                {
                    index = stoi(s1);
                    if(index <= range && index >= 0)
                    {
                        done = false;
                    }
                    else
                    {
                        std::cout<<"Out of range. Please re-enter.\n";
                        done = true;
                    }
                }
            }
        } while(done);

        nconst = actor_to_id_[s][index];
     //   std::cin.ignore(256, '\n');
        return true;
    }

    return !s.empty();
}
