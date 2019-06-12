#include "../include/graph.h"

/**
 * the graph gets all the information from the parse class
 * @brief Graph::Graph
 */
Graph::Graph() {
    parser_.PopulateActors(actor_to_id_,actorIndex_, actorMovies_);
    parser_.PopulateCast(actorIndex_, actorMovies_, movieCrew_, movieIndex_);
    parser_.PopulateTitles(movies_);

}

/**
 * Clears everything, the maps clear automaticlly at the end of a funct
 * @brief Graph::~Graph
 */
Graph::~Graph() {
    actorMovies_.clear();
    movieCrew_.clear();
}

/**
 * Does the Breadth frist search depending ont the start actor
 * and end actor with the help of wiki's pseudocode
 * https://en.wikipedia.org/wiki/Breadth-first_search
 *
 * @brief Graph::BreadthFirstSearch
 * @param actorNameFrom actor from bacon number
 * @param actorNameTo actor to
 */
void Graph::BreadthFirstSearch(int &actorNameFrom, int &actorNameTo) {
    cs8::Queue<int> sixDegrees;
    std::stringstream ss;
    int actor;
    std::string lastName;

    ss.str(actorMovies_[actorIndex_[actorNameTo]]->name);
    ss>>lastName>>lastName;
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

    actorMovies_[actorIndex_[actorNameFrom]]->visited = true;
    sixDegrees.enqueue(actorNameFrom);



    int movieIndex, actorIndex, baconNumber = 0;

    if(actorNameFrom == actorNameTo)
    {
        std::cout<<"------------------------------\n";
        std::cout<<actorMovies_[actorIndex_[actorNameFrom]]->name<<"'s "<<lastName<<" Number is 0.\n";
        std::cout<<"------------------------------\n";
        return;
    }

    if(actorMovies_[actorIndex_[actorNameTo]]->movies.empty())
    {
        std::cout<<"Insufficient data for chosen person(s).\n";
        return;
    }

    while(!sixDegrees.empty())
    {
        actor = sixDegrees.dequeue();
        //if the person has not been visited
       // if(actorMovies_[actorIndex_[actor]]->visited == false) //actorMovies_[actorIndex_[actor]] actor is the id that is put in actorIndex_ to get a index to get the information of an actor in actorMovies_ vector
        //{
            //set to being visited
           // actorMovies_[actorIndex_[actor]]->visited = true;
            //Go thru their movies
            for(int i = 0; i < actorMovies_[actorIndex_[actor]]->movies.size(); ++i)
            {
                //TODO: IMPLEMENT MAP PROTECTOR
//                int test = actorMovies_[actorIndex_[actor]]->movies[i];
//                if(movies_.Count(test))
//                std::string moviename = movies_[test];
                movieIndex = movieIndex_[actorMovies_[actorIndex_[actor]]->movies[i]];

                //actorMovies_[actorIndex_[actor]]->movies[i]] returns a tconst that you put in movie index
                if(movieCrew_[movieIndex]->visited == false)
                {
                    //set movie to being visited true so reprocessing does have to be done
                    movieCrew_[movieIndex]->visited = true;
                  // std::cout<<'\n'<< movies_[movieCrew_[movieIndex]->movieID]<<'\n';
                    //check the actors in the movie
                    for(int j = 0; j < movieCrew_[movieIndex]->actors.size(); ++j)
                    {

                        actorIndex = actorIndex_[movieCrew_[movieIndex]->actors[j]];
                        //if the actor equals the chosen one
                        if(movieCrew_[movieIndex]->actors[j] == actorNameTo)
                        {
                            if(actorMovies_[actorIndex]->name != actorMovies_[actorIndex_[actor]]->name)
                            {
                                actorMovies_[actorIndex_[actorNameTo]]->parent = actorMovies_[actorIndex_[actor]];
                                actorMovies_[actorIndex_[actorNameTo]]->parentM = movieCrew_[movieIndex];
                            }


                            Actor *actorTemp = actorMovies_[actorIndex_[actorNameTo]];

                            std::cout<<"------------------------------\n";
                            if(movies_.Count(actorTemp->parentM->movieID) == 1)
                                std::cout<<actorTemp->name<<"\n WITH \n"<<movies_[actorTemp->parentM->movieID] <<"\n IN \n";
                            else
                                std::cout<<actorTemp->name<<"\n WITH \n"<<"Movie not found" <<"\n IN \n";

                            for(actorTemp = actorTemp->parent ; actorTemp != nullptr; actorTemp = actorTemp->parent)
                            {
                                if(actorTemp->parent == nullptr)
                                    std::cout<<actorTemp->name;
                                else
                                {
                                    if(movies_.Count(actorTemp->parentM->movieID) == 1)
                                        std::cout<<actorTemp->name<<"\n WITH \n"<<movies_[actorTemp->parentM->movieID]<< "\n IN \n";
                                    else
                                        std::cout<<actorTemp->name<<"\n WITH \n"<<"Movie not found" <<"\n IN \n";
                                }
                                ++baconNumber;
                            }
                            std::cout<<'\n';
                            std::cout<<actorMovies_[actorIndex_[actorNameFrom]]->name<<"'s "<<lastName<<" number is "<<baconNumber<<'\n';
                            std::cout<<"------------------------------\n";
                            return;
                        }
                        else
                        {
                            //Enqueue Actor that isnt the same actor

                           // std::cout<<actorMovies_[actorIndex_[movieCrew_[movieIndex]->actors[j]]]->name<<" , ";
                            if(actorMovies_[actorIndex]->visited == false)
                            {
                                if(actorMovies_[actorIndex]->name != actorMovies_[actorIndex_[actor]]->name)
                                {
                                    actorMovies_[actorIndex]->parent = actorMovies_[actorIndex_[actor]];
                                    actorMovies_[actorIndex]->parentM = movieCrew_[movieIndex];
                                }
                                actorMovies_[actorIndex]->visited = true;
                                sixDegrees.enqueue(actorMovies_[actorIndex]->actorID);
                                //movieCrew_[movieIndex]->actors[j]
                            }
                        }
                    }
                }
            }
       // }
    }
    std::cout<<"Insufficient data for chosen person(s).\n";
}

/**
 * Based on the Levenshtein distance https://en.wikipedia.org/wiki/Levenshtein_distance
 * and https://rosettacode.org/wiki/Levenshtein_distance
 *
 * @brief LevenshteinDistance
 */
int LevenshteinDistance(const std::string &nameOne, const std::string &nameTwo)
{
    unsigned int nameOneInt = nameOne.size(), nameTwoInt = nameTwo.size();
    if( nameOneInt==0 ) return nameTwoInt;
    if( nameTwoInt==0 ) return nameOneInt;
    unsigned int *diff = new unsigned int[nameTwoInt + 1];
    for(unsigned int k=0; k<=nameTwoInt; k++)
        diff[k] = k;
    for (unsigned int i = 0; i <nameOne.size();++i ){
        diff[0] = i+1;
        unsigned int index = i;
        for (unsigned int j = 0; j <nameTwo.size();++j ){
            unsigned int upper = diff[j+1];
            if( nameOne[i] == nameTwo[j] ){
                diff[j+1] = index;
            }
            else{
                unsigned int t = upper < index ? upper : index;
                diff[j+1] = (diff[j] < t ? diff[j] : t)+1;
            }
            index = upper;
        }
    }
    unsigned int difference = diff[nameTwoInt];
    delete [] diff;
    return difference;
}

/**
 * Input validation for multiple actor names
 * @brief Graph::GraphGetInput
 * @param nconst
 * @param question
 * @return
 */
bool Graph::GraphGetInput(int &nconst, std::string &&question)
{
    bool found = false, done = true;
    int index = 0, range = 0;
    int notInt;
    std::string s, s1;
    printf("%s\n", question.c_str());
    int distance = 0, tempw = 0, indexw = 0;

    while(!found)
    {
        getline(std::cin, s);
        if(s.empty())
        {
            return false;
        }
        if(!actor_to_id_.Count(s))
        {
            distance = LevenshteinDistance(s, actorMovies_[0]->name);
            if(distance != 0)
            for(unsigned int i = 1; i < actorMovies_.size(); ++i)
            {
                if(toupper(s[0]) == toupper(actorMovies_[i]->name[0]))
                {
                    tempw =  LevenshteinDistance(s,actorMovies_[i]->name);
                    if(tempw == 0)
                    {
                        indexw = i;
                        break;
                    }
                    if(distance > tempw)
                    {
                        distance = tempw;
                        indexw = i;
                    }
                }
            }
            std::cout<<"Name not found, did you mean "<< actorMovies_[indexw]->name<<'\n';
        }
        else
            found = true;
    }



    if(actor_to_id_[s].size() == 1)
    {
        nconst = actorMovies_[actorIndex_[actor_to_id_[s][0]]]->actorID;
        return true;
    }
    else
    {
        std::cout<<"Duplicate actors, which actor?\n";
        for(unsigned int i = 0; i < actor_to_id_[s].size(); ++i)
        {
            std::cout<<i<<':';
            if(actorMovies_[actorIndex_[actor_to_id_[s][i]]]->famousMovies.size() != 0)
            {
                for(unsigned int j = 0; j < actorMovies_[actorIndex_[actor_to_id_[s][i]]]->famousMovies.size(); ++j)
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
        //Input validation for correct index
        do {
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
        return true;
    }
}
