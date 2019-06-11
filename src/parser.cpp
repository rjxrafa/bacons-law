#include "../include/parser.h"
#include "../include/graph.h"

/**
 * @brief Parser::Parser
 * tconst : title alphanumeric identifier
 * nconst : actor name alphanumeric identifier
 */
Parser::Parser() = default;

Parser::~Parser() = default;

/**
 * This function populates a given map with the key value pair of actor ids and their respective names.
 *
 * @param actors
 */
void Parser::PopulateActors(cs8::Map<std::string, std::vector<int>> &actorToId,
                            cs8::Map<int, int> &actorID, std::vector<Actor*> &actorMovs) {

    std::stringstream ss;
    std::string temp,     // Placeholder string
            nconst,   // Actor ID
            name,     // Actor Name
            titles;   // Top Movies
    int nconstInt;
    std::cout<<"Parsing actors.tsv.\n";
    if (OpenFile(FILE_OPEN::INPUT, "actors.tsv"))
    {
        getline(in, temp); // skip first line
        for (int i = 0; !in.eof(); ++i) {
            getline(in, nconst, '\t');
            getline(in, name, '\t');
            getline(in, temp, '\t');
            getline(in, temp, '\t');
            getline(in, temp, '\t');
            getline(in, titles);
            nconst.erase(0,2);
            nconstInt = stoi(nconst);

            if(actorToId.Count(name) == 0)
            {
                actorToId.Insert(name, std::vector<int>());
                actorToId[name].push_back(nconstInt);
            }
            else
                actorToId[name].push_back(nconstInt);
            actorID.Insert(nconstInt, i);

            Actor *s = new Actor(name,nconstInt);
            if(titles != "\\N")
            {
                if(titles.find(',') != std::string::npos)
                {
                    std::replace(titles.begin(),titles.end(),',',' ');
                    ss.str(titles);
                    ss.clear();
                    while(ss>>temp)
                    {
                        s->famousMovies.push_back(getPopularTitles(temp));
                    }

                }
                else
                {
                    s->famousMovies.push_back(getPopularTitles(titles));
                }
            }
            actorMovs.push_back(s);
        }
        in.close();
    }
}

/**
 * This function adds movies to the actors and creats the crew of the movies
 *
 * @param actorID
 * @param actorMovs
 * @param movieCrew
 * @param movieID
 */
void Parser::PopulateCast(cs8::Map<int, int> &actorID, std::vector<Actor*> &actorMovs, std::vector<Crew*> &movieCrew,
                          cs8::Map<int, int> &movieID) {

    std::string temp,     // Placeholder string
            tconst,   // Title ID
            nconst,   // Name ID
            category; // Job
    int nconstInt, tconstInt;
    int index = 0;
    //Casting info w/ movie id
    std::cout<<"Parsing cast.tsv.\n";
    if(OpenFile(Parser::FILE_OPEN::INPUT,"cast.tsv"))
    {
        getline(in, temp); // skips first line
        for (int i = 0; !in.eof(); ++i) {
            getline(in,tconst,'\t');
            getline(in,temp,'\t');
            getline(in,nconst,'\t');
            getline(in,category,'\t');
            getline(in, temp);
            tconst.erase(0,2);
            nconst.erase(0,2);
            tconstInt = stoi(tconst);
            nconstInt = stoi(nconst);
            if(category[0] == 'a' && actorID.Count(nconstInt))
            {
                actorMovs[actorID[nconstInt]]->movies.push_back(tconstInt);// push movie followed by space

                if(!movieID.Count(tconstInt))
                {
                    movieID.Insert(tconstInt, index);
                    ++index;
                    Crew *s = new Crew();
                    s->movieID = tconstInt;
                    //s->hasBeenUsed = false;
                    s->actors.push_back(stoi(nconst));
                    movieCrew.push_back(s); //push back into [0] movie [1] crew;
                }
                else
                {
                    movieCrew[movieID[tconstInt]]->actors.push_back(nconstInt);
                }
            }
        }
        in.close();
    }
}

/**
 * This function uses the dataset of 'titles.tsv' and parses inserts them into a
 * given map.
 *
 * Uses a key value pair of title ID against the movie title.
 *
 * @param movie_titles
 */
void Parser::PopulateTitles(cs8::Map<int, std::string> &movie_titles) {
    //  std::string temp;
    std::string temp,     // Placeholder string
            tconst,   // Title ID
            title;    // Movie Title

    //  Movie title & ID
    std::cout<<"Parsing titles.tsv.\n";
    if(OpenFile(Parser::FILE_OPEN::INPUT,"titles.tsv"))
    {
        getline(in, temp);  // Skip first line
        for (int i = 0; !in.eof(); ++i) {
            getline(in, tconst, '\t');
            getline(in, temp, '\t');
            getline(in, title, '\t');
            getline(in, temp);
            tconst.erase(0,2);
            movie_titles.Insert(stoi(tconst), title);
        }
        in.close();
    }
}

bool Parser::OpenFile(Parser::FILE_OPEN type, std::string fileName) {
    if (type == FILE_OPEN::INPUT) {
        std::string input;

        while (1) {
            in.open(fileName);//1 is names

            if (in.good()) {
                printf("File opened!\n");
                return true;
            }
            else
            {
                printf("File not found, please have the?\n"
                       "actors, cast, and titles .tsv");
                exit(0);
            }
        }
    }
    return true;
}

/**
 * Erases first two of the t const or n const because they
 * are not numbers needed for stoi
 * @param title
 */
int Parser::getPopularTitles(std::string &title)
{
    title.erase(0,2);
    return stoi(title);
}
