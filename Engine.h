//
// Created by jordan on 5/10/19.
//

#ifndef SNEK_ENGINE_H
#define SNEK_ENGINE_H
#include "ncurses.h"
#include "Snake.h"
#include "Food.h"
#include <list>

enum class GameState
{
    BEGIN,
    MAIN,
    END
};


class Engine
{
public:
    Engine();
    Engine(WINDOW* gameWindow, int players);
    void Begin();
    void MainLoop();
    void End();

protected:
    int numPlayers;
    WINDOW* win;
    list<GameObject> gameObjects;
};


#endif //SNEK_ENGINE_H
