//
// Created by jordan on 5/10/19.
//

#ifndef SNEK_ENGINE_H
#define SNEK_ENGINE_H
#include "ncurses.h"
#include "Snake.h"
#include "Food.h"
#include <list>
#include <memory>
using std::shared_ptr;
using std::unique_ptr;

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
    virtual ~Engine() = default;
    bool areAnyDead();
    template <typename T> list<shared_ptr<T>> FindGOByType();

    void addGameObject(shared_ptr<GameObject> go);
    void RunGame();
    int numGameObjects();
    template <typename T> bool isType(shared_ptr<GameObject> go);



protected:

    void processCollisions();
    void processDestroyed();

    int                 numPlayers  =   0;
    WINDOW*             win         =   nullptr;
    GameState           state       =   GameState::BEGIN;
    list<shared_ptr<GameObject>>    gameObjects;
    unique_ptr<InputRouter> inputRouter = nullptr;

private:

};


#endif //SNEK_ENGINE_H
