/****
 * @author      Rafael Betita & Ara Mico Segismundo
 * @modified    06-1-2019
 ****/

#include "../include/parser.h"

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
void Parser::PopulateActors(std::map<std::string, std::string> &actors) {

  std::string temp,     // Placeholder string
              nconst,   // Actor ID
              name;     // Actor Name

  if (OpenFile(FILE_OPEN::INPUT, "actors.tsv")) {
    std::getline(in, temp); // skip first line
    for (int i = 0; !in.eof(); ++i) {
      std::getline(in, nconst, '\t');
      std::getline(in, name, '\t');
      std::getline(in, temp, '\n');

      actors.insert(str_pair(nconst, name));

    }
    in.close();
  }
}

void Parser::PopulateCast(std::map<std::string, std::string> &movies) {

  std::string temp,     // Placeholder string
              tconst,   // Actor ID
              name;     // Actor Name

//  Casting info w/ movie id
//  if(OpenFile(Parser::FILE_OPEN::INPUT,"cast.tsv"))
//  {
//    getline(in, temp); // skips first line
//    for (int i = 0; !in.eof(); ++i) {
//      in>>tconst>>temp>>nconst>>category;
//      getline(in, temp);
//      if(category[0] == 'a')
//        printf("%d: %s, %s, %s\n", i, tconst.c_str(), nconst.c_str(), category.c_str());
//    }
//    in.close();
//  }
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

