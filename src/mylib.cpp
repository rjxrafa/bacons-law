/****
 * @author      Rafael Betita & Ara Mico Segismundo
 * @modified    06-1-2019
 ****/

#include "../include/mylib.h"

bool GetInput(std::string &input, std::string &&question) {

  printf("%s\n", question.c_str());

  getline(std::cin, input);
  fflush(stdin);

  return !input.empty();
}

