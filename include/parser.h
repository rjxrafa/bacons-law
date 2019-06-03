/****
 * @author      Rafael Betita & Ara Mico Segismundo
 * @modified    06-1-2019
 ****/

#ifndef BACONS_LAW_SRC_PARSER_H_
#define BACONS_LAW_SRC_PARSER_H_

#define str_pair std::pair<std::string, std::string>
#define str_int_pair std::pair<std::string, int>
#define actor_pair std::pair<std::string, std::vector<std::string>*>

#include "mylib.h"
#include <string>

class Parser {

  enum class FILE_OPEN{INPUT, OUTPUT};

public:
  Parser();
  ~Parser() = default;
  Parser(const Parser &other);
  Parser& operator=(const Parser &other);

  void PopulateCast(std::map<std::string, int> &actorID, std::vector<std::string *> &actorMovs, std::vector<std::string *> &movieC,
                    std::map<std::string, int> &movieID);
  void PopulateTitles(std::map<std::string, std::string> &actors);
  void PopulateActors(std::map<std::string, int> &actorID, std::vector<std::string*> &actorMovs);

 private:
  std::ifstream in;
  std::ofstream out;
  bool OpenFile(FILE_OPEN type, std::string fileName);
};

#endif //BACONS_LAW_SRC_PARSER_H_
