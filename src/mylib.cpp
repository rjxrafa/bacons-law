#include "../include/mylib.h"

/**
 * Checks whether there is input, and changes it.
 * @brief GetInput
 * @param input
 * @param question
 */
bool GetInput(std::string &input, std::string &&question) {
    printf("%s\n", question.c_str());

    getline(std::cin, input);

    return !input.empty();
}
