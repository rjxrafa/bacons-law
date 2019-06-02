//
// Created by rafab on 6/1/2019.
//

#include "../include/parser.h"

Parser::Parser() {
  while (!OpenFile(Parser::FILE_OPEN::INPUT));
  std::string temp;
  std::string name_identifier, name;
  int name_int;

  //skipping first line
  getline(in, temp);
  //for names
  for (int i = 0; !in.eof(); ++i) {
    getline(in, name_identifier, '\t');
    getline(in, name, '\t');
    getline(in, temp);
    name_identifier.erase(0,2);
    printf("%d: %s, %s\n", i, name_identifier.c_str(), name.c_str());
    name_int = std::stoi(name_identifier);
  }
  in.close();

}

bool Parser::OpenFile(Parser::FILE_OPEN type) {

  if (type == FILE_OPEN::INPUT) {
    std::string input;

    while (1) {
      while(!GetInput(input, "Enter filename: "));

      in.open("1.tsv");//1 is names

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
