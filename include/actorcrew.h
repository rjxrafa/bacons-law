#ifndef ACTORCREW_H
#define ACTORCREW_H

#include<vector>

struct Actor
{
    int actorID;
    std::vector<int> movies;
    std::vector<int> famousMovies;
    bool hasBeenUsed;
};

struct Crew
{
    int movieID;
    std::vector<int> actors;
    bool hasBeenUsed;
};

#endif // ACTORCREW_H
