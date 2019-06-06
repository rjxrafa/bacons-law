#ifndef ACTORCREW_H
#define ACTORCREW_H

#include<vector>

struct Actor
{
    Actor(int id = 0){
        actorID = id;
    }
    ~Actor(){
        actorID = 0;
        movies.clear();
        famousMovies.clear();
    }
    int actorID;
    std::vector<int> movies;
    std::vector<int> famousMovies;
//    bool hasBeenUsed;
};

struct Crew
{
    Crew(int id = 0){
        movieID = id;
    }
    ~Crew(){
        movieID = 0;
        actors.clear();
    }
    int movieID;
    std::vector<int> actors;
//    bool hasBeenUsed;
};

#endif // ACTORCREW_H
