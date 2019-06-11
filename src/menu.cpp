#include "../include/menu.h"

Menu::Menu() = default;

Menu::~Menu() = default;

void Menu::Run()
{
    // clock_t start = clock();
    //  Parser a;
    //  clock_t stop = clock();
    //  double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    //   printf("Time elapsed in ms: %f", elapsed);
        clock_t startTime = clock();

    //    Parser a;

        Graph Kevin;
        int person1, person2;
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        while(Kevin.GraphGetInput(person1,"Actor from:") && Kevin.GraphGetInput(person2,"Actor to:"))
        {
            Kevin.BreadthFirstSearch(person1,person2);
        }

}
