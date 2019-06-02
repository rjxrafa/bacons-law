/****
 * @author      Rafael Betita & Ara Mico Segismundo
 * @modified    06-1-2019
 ****/

#ifndef BACONS_LAW_SRC_PARSER_H_
#define BACONS_LAW_SRC_PARSER_H_

#include "mylib.h"
#include <string>

class Parser {

  enum class FILE_OPEN{INPUT, OUTPUT};

public:
  Parser();
  ~Parser() = default;
  Parser(const Parser &other);
  Parser& operator=(const Parser &other);

  bool OpenFile(FILE_OPEN type, std::string fileName);

private:
  std::ifstream in;
  std::ofstream out;



};

#endif //BACONS_LAW_SRC_PARSER_H_
