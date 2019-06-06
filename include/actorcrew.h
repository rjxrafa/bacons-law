#ifndef ACTORCREW_H
#define ACTORCREW_H

#include<vector>

struct Actor
{
    Actor(int id = 0){
        actorID = id;
        visited = false;
    }
    ~Actor(){
        actorID = 0;
        movies.clear();
        famousMovies.clear();
        visited = false;
    }
    int actorID;
    std::vector<int> movies;
    std::vector<int> famousMovies;
    bool visited;
};

struct Crew
{
    Crew(int id = 0){
        movieID = id;
        visited = false;
    }
    ~Crew(){
        movieID = 0;
        actors.clear();
        visited = false;
    }
    int movieID;
    std::vector<int> actors;
    bool visited;
};

#endif // ACTORCREW_H
