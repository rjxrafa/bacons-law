/****
 * @author      Rafael Betita & Ara Mico Segismundo
 * @modified    06-1-2019
 ****/

#include "../include/parser.h"
#include "../include/graph.h"

/**
 * @brief Parser::Parser
 * tconst : title alphanumeric identifier
 * nconst : actor name alphanumeric identifier
 */
Parser::Parser() {

}

/**
 * This function populates a given map with the key value pair of actor ids and their respective names.
 *
 * @param actors
 */
void Parser::PopulateActors(std::map<std::string, std::vector<int>> &actorToId, std::map<int, int> &actorID, std::vector<Actor*> &actorMovs) {

  std::stringstream ss;
  std::string temp,     // Placeholder string
              nconst,   // Actor ID
              name,     // Actor Name
              titles;   // Top Movies
  int nconstInt;

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
        //  std::cout<<titles<<'\n';
          if(actorToId.count(name) == 0)
          {
              actorToId.insert(std::pair<std::string, std::vector<int>>(name, std::vector<int>()));
              actorToId.at(name).push_back(nconstInt);
          }
          else
              actorToId.at(name).push_back(nconstInt);
          actorID.insert(int_pair(nconstInt, i));
          //rafa tree overload [] use find to return an int
          //if titles == \n
          Actor *s = new Actor();
          s->actorID = nconstInt;
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

void Parser::PopulateCast(std::map<int, int> &actorID, std::vector<Actor*> &actorMovs, std::vector<Crew*> &movieCrew,
                          std::map<int, int> &movieID) {

  std::string temp,     // Placeholder string
              tconst,   // Title ID
              nconst,   // Name ID
              category; // Job
  int nconstInt, tconstInt;
  int index = 0;
  //Casting info w/ movie id
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
          if(category[0] == 'a' && actorID.count(nconstInt))
          {
              actorMovs[actorID[nconstInt]]->movies.push_back(tconstInt);// push movie followed by space

              if(!movieID.count(tconstInt))
              {
                  movieID.insert(int_pair(tconstInt, index));
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

          //          movies[actorID[nconst]].second->push_back(tconst);
          //          cast.insert(str_pair(tconst, nconst));
          //        printf("%d: %s, %s, %s\n", i, tconst.c_str(), nconst.c_str(), category.c_str());
      }
      in.close();
  }
}

/**
 * This function uses the dataset of 'titles.tsv' and parses for all US region movies and inserts them into a
 * given map.
 *
 * Uses a key value pair of title ID against the movie title.
 *
 * @param movie_titles
 */
void Parser::PopulateTitles(std::map<std::string, std::string> &movie_titles) {
  //  std::string temp;
  std::string temp,     // Placeholder string
              tconst,   // Title ID
              title,    // Movie Title
              lang;     // Region

  //  Movie title & ID
  if(OpenFile(Parser::FILE_OPEN::INPUT,"titles.tsv"))
  {
    getline(in, temp);  // Skip first line
    for (int i = 0; !in.eof(); ++i) {
      getline(in, tconst, '\t');
      getline(in, temp, '\t');
      getline(in, title, '\t');
      getline(in, lang, '\t');
      getline(in, temp);
      if(lang == "US") {
        movie_titles.insert(str_pair(tconst, title));
      }
    }
    in.close();
  }
}

bool Parser::OpenFile(Parser::FILE_OPEN type, std::string fileName) {

//  if (type == FILE_OPEN::INPUT) {
//    std::string input;

//    while (1) {
//      while(!GetInput(input, "Enter filename: "));

  in.open(fileName);//1 is names

//      if (in.good()) {
//        printf("File opened!\n");
//        return true;
//      }
//      else
//        printf("File not found!\n");
//        return false;
//    }

//  } else {

//  }
  return true;
}

int Parser::getPopularTitles(std::string &title)
{
    title.erase(0,2);
    return stoi(title);
}

