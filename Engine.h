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

    /* Constructors */
    Engine();
    Engine(WINDOW* gameWindow, int players);

    /* Game Loops */
    void Begin();
    void MainLoop();
    void End();

    /* Destructor */
    virtual ~Engine() = default;

    template <typename T>
    std::list<shared_ptr<T>>    FindGOByType();
    bool                        areAnyDead();
    void                        addGameObject(shared_ptr<GameObject> go);
    void                        RunGame();
    int                         numGameObjects();
    std::list<std::shared_ptr<GameObject>> FindAllByTag(Tag tag);
protected:

    void processCollisions();
    void processDestroyed();

    int                                 numPlayers  {0};
    WINDOW*                             win         {nullptr};
    GameState                           state       {GameState::BEGIN};
    std::list<shared_ptr<GameObject>>   gameObjects {};
    unique_ptr<InputRouter>             inputRouter {nullptr};


};


extern std::shared_ptr<Engine> gameEngine;


#endif //SNEK_ENGINE_H
