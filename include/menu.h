/**
 * This is a menu interface to give user choices
 *
 * @authors  Rafael Betita and Ara Mico Segismundo
 * @modified 2019-06-10
 */

#ifndef MENU_H
#define MENU_H

#include "parser.h"
#include "graph.h"
#include "mylib.h"
#include "myqueue.h"
#include <ctime>

class Menu
{
public:
    Menu();
    ~Menu();

    void Run();
};

#endif // MENU_H
