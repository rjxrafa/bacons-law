/****
 * @author      Rafael Betita & Ara Mico Segismundo
 * @modified    06-1-2019
 ****/

#include "../include/parser.h"

/**
 * @brief Parser::Parser
 * tconst = title alphanumeric identifier
 * nconst = actor name alphanumeric identifier
 */
Parser::Parser() {
  std::string temp;
  std::string nconst, name, tconst, category, title, lang;
  int name_int;

  in.clear();
  //for names
  if(OpenFile(Parser::FILE_OPEN::INPUT,"1.tsv"))
  {
      //skipping first line
      getline(in, temp);
      for (int i = 0; !in.eof(); ++i) {
          getline(in, nconst, '\t');
          getline(in, name, '\t');
          getline(in, temp);
          nconst.erase(0,2);
//          if(i%100000 == 0)
//          printf("%d: %s, %s\n", i, nconst.c_str(), name.c_str());
          name_int = std::stoi(nconst);
      }
      in.close();
  }

  in.clear();
//  for nameid to movie title
  if(OpenFile(Parser::FILE_OPEN::INPUT,"2.tsv"))
  {
      //skipping first line
      getline(in, temp);
      for (int i = 0; !in.eof(); ++i) {
          in>>tconst>>temp>>nconst>>category;
          getline(in, temp);
          if(in.eof());//do something;
          printf("%d: %s, %s, %s\n", i, tconst.c_str(), nconst.c_str(), category.c_str());
      }
      in.close();
  }

  in.clear();
//  for title id to title name
  if(OpenFile(Parser::FILE_OPEN::INPUT,"3.tsv"))
  {
      //skipping first line
      getline(in, temp);
      for (int i = 0; !in.eof(); ++i) {
          getline(in, tconst, '\t');
          getline(in, temp, '\t');
          getline(in, title, '\t');
          getline(in, lang, '\t');
          getline(in, temp);
          if(lang == "US");//do something;
         // printf("%d: %s, %s, %s\n", i, tconst.c_str(), title.c_str(), lang.c_str());
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
