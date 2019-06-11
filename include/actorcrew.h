/**
 * These are nodes used in the graph class to create connections
 * and use necessary information between the actors and movies
 *
 * @author      Ara Mico Segismundo & Rafael Betita
 * @modified    2019-06-10
 */

#ifndef ACTORCREW_H
#define ACTORCREW_H

#include<vector>
#include<string>

//Crew Holds the id of the movie, all the actor ids, and if its been visited
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

//Actor holds the movies they were in with the other
//the name of the actor, the id, movieIDs, and their famous movieIDs
struct Actor
{
    Actor(std::string s = "", int id = 0){
        name = s;
        actorID = id;
        visited = false;
        parent = nullptr;
        parentM = nullptr;
    }
    ~Actor(){
        actorID = 0;
        movies.clear();
        famousMovies.clear();
        visited = false;
        parent = nullptr;
        parentM = nullptr;
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
