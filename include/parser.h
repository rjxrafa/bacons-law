/****
 * @author      Rafael Betita & Ara Mico Segismundo
 * @modified    06-1-2019
 ****/

#ifndef BACONS_LAW_SRC_PARSER_H_
#define BACONS_LAW_SRC_PARSER_H_

#define str_pair std::pair<std::string, std::string>
#define str_int_pair std::pair<std::string, int>
#define int_pair std::pair<int, int>

#include "mylib.h"

class Parser {

  enum class FILE_OPEN{INPUT, OUTPUT};

public:
  Parser();
  ~Parser() = default;
  Parser(const Parser &other);
  Parser& operator=(const Parser &other);

  void PopulateCast(std::map<int, int> &actorID, std::vector<Actor *> &actorMovs, std::vector<Crew *> &movieCrew,
                    std::map<int, int> &movieID);
  void PopulateTitles(std::map<int, std::string> &actors);
  void PopulateActors(std::map<std::string, std::vector<int> > &actorToId, std::map<int, int> &actorID, std::vector<Actor *> &actorMovs);

 private:
  int getPopularTitles(std::string &title);
  std::ifstream in;
  std::ofstream out;
  bool OpenFile(FILE_OPEN type, std::string fileName);
};

#endif //BACONS_LAW_SRC_PARSER_H_
