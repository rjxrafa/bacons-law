#ifndef ACTORCREW_H
#define ACTORCREW_H

#include<vector>
#include<string>

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

struct Actor
{
    Actor(std::string s = "", int id = 0){
        name = s;
        actorID = id;
        visited = false;
        parent = nullptr;
    }
    ~Actor(){
        actorID = 0;
        movies.clear();
        famousMovies.clear();
        visited = false;
        parent = nullptr;
    }
    std::string name;
    int actorID;
    std::vector<int> movies;
    std::vector<int> famousMovies;
    bool visited;
    Actor* parent;
    Crew* parentM;
};

#endif // ACTORCREW_H
