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
        std::string actor;
        std::cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << std::endl;
        while(GetInput(actor,"Movie's Name?"))
        {
            Kevin.GetActorName(actor);
        }

}
