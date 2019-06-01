//
// Created by rafab on 6/1/2019.
//

#include "../include/parser.h"

Parser::Parser() {
  while (!OpenFile(Parser::FILE_OPEN::INPUT));
  std::string temp;

  for (int i = 0; i < 20; ++i) {
    getline(in, temp);
    printf("%d: %s\n", i, temp.c_str());
  }
  in.close();

}

bool Parser::OpenFile(Parser::FILE_OPEN type) {

  if (type == FILE_OPEN::INPUT) {
    std::string input;

    while (1) {
      while(!GetInput(input, "Enter filename: "));

      in.open(input);

      if (in.good()) {
        printf("File opened!\n");
        return true;
      }
      else
        printf("File not found!\n");
        return false;
    }

  } else {

  }

}
