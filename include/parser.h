/**
 * @author      Rafael Betita & Ara Mico Segismundo
 * @modified    2019-06-08
 */

#ifndef BACONS_LAW_SRC_PARSER_H_
#define BACONS_LAW_SRC_PARSER_H_

#include "mylib.h"
/**
 * Class to parse imdb files
 * @brief The Parser class
 */
class Parser {

    enum class FILE_OPEN{INPUT, OUTPUT};

public:
    Parser();
    ~Parser();

    void PopulateCast(cs8::Map<int, int> &actorID, std::vector<Actor *> &actorMovs, std::vector<Crew *> &movieCrew,
                      cs8::Map<int, int> &movieID);
    void PopulateTitles(cs8::Map<int, std::string> &movie_titles);
    void PopulateActors(cs8::Map<std::string, std::vector<int> > &actorToId, cs8::Map<int, int> &actorID, std::vector<Actor *> &actorMovs);

private:
    int getPopularTitles(std::string &title);
    std::ifstream in;
    std::ofstream out;
    bool OpenFile(FILE_OPEN type, std::string fileName);
};

#endif //BACONS_LAW_SRC_PARSER_H_
