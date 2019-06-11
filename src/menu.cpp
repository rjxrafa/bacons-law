#include "../include/menu.h"

Menu::Menu() = default;

Menu::~Menu() = default;

/**
 * Function that runs the program
 * @brief Menu::Run
 */
void Menu::Run(){
    clock_t startTime = clock();
    Graph Kevin;
    int person1, person2;
    std::cout <<"Parsing time: "
             << double( clock() - startTime ) / (double)CLOCKS_PER_SEC
             << " seconds." << std::endl;
    while(1)
    {
        if(Kevin.GraphGetInput(person1,"Actor from:") && Kevin.GraphGetInput(person2,"Actor to:"))
        {
            Kevin.BreadthFirstSearch(person1,person2);
        }
        else
            std::cout<<"Actor name empty.\n";
    }
}
