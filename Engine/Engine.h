//
// Created by jordan on 5/10/19.
//

#ifndef SNEK_ENGINE_H
#define SNEK_ENGINE_H

#include <list>
#include <memory>
#include <ncurses.h>
#include "Scene.h"
#include "GameObjects/Snake.h"
#include "GameObjects/Food.h"

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
    Engine(int players);

    /* Game Loops */
    void Begin();
    void MainLoop();
    void End();

    /* Destructor */
    virtual ~Engine() = default;

    template <typename T>
    std::list<shared_ptr<T>>    FindGOByType();
    bool                        areAnyDead();
    void                        changeScene(int newScene);
    void                        changeScene(std::string sceneName);
    void                        quit();
    void                        addGameObject(shared_ptr<GameObject> go);
    void                        RunGame();
    int                         numGameObjects();
    int                         getInput();
    std::list<std::shared_ptr<GameObject>> FindAllByTag(Tag tag);

    bool gameObjectAtLocation(int y, int x);

protected:

    void processCollisions();
    void processDestroyed();
    void internalChangeScene();



    int                                     numPlayers      {0};
    //WINDOW*                                 win           {nullptr};
    GameState                               state           {GameState::BEGIN};
    //std::list<shared_ptr<GameObject>>     gameObjects     {};
    std::vector<std::shared_ptr<Scene>>     scenes          {};
    unique_ptr<InputRouter>                 inputRouter     {nullptr};
    int                                     gameSleep       {200};
    int                                     currentScene    {0};
    bool                                    shouldQuit      {false};
    bool                                    shouldChangeScene {false};
    int                                     requestedSceneChange {0};

};


extern std::shared_ptr<Engine> gameEngine;


#endif //SNEK_ENGINE_H
