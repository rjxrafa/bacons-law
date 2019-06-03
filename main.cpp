#include "include/parser.h"
#include "include/graph.h"
#include <ctime>

using namespace std;
int main() {

// clock_t start = clock();
//  Parser a;
//  clock_t stop = clock();
//  double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
//   printf("Time elapsed in ms: %f", elapsed);
    clock_t startTime = clock();

//    Parser a;

    Graph test;
    std::string actor;
    cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
    while(GetInput(actor,"Movie's Name?"))
    {
        test.GetCast(actor);
    }


    return 99;

}
