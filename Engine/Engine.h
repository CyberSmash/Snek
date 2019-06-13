//
// Created by jordan on 5/10/19.
//

#ifndef SNEK_ENGINE_H
#define SNEK_ENGINE_H

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include <list>
#include <memory>
#include <ncurses.h>

#include "Scene.h"
#include "GameObjects/Snake.h"
#include "GameObjects/Food.h"


namespace logging = boost::log;

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
    std::list<std::shared_ptr<T>>    FindGOByType();
    bool                        areAnyDead();
    void                        changeScene(int newScene);
    void                        changeScene(std::string sceneName);
    void                        quit();
    void                        addGameObject(std::shared_ptr<GameObject> go);
    void                        RunGame();
    int                         numGameObjects();
    int                         getInput();
    std::list<std::shared_ptr<GameObject>> FindAllByTag(Tag tag);

    bool gameObjectAtLocation(int y, int x);
    void getLogger();


protected:

    void processCollisions();
    void processDestroyed();
    void internalChangeScene();


    int                                     numPlayers              {0};
    GameState                               state                   {GameState::BEGIN};
    std::vector<std::shared_ptr<Scene>>     scenes                  {};
    std::unique_ptr<InputRouter>            inputRouter             {nullptr};
    int                                     gameSleep               {200};
    int                                     currentScene            {0};
    bool                                    shouldQuit              {false};
    bool                                    shouldChangeScene       {false};
    int                                     requestedSceneChange    {0};

    logging::sources::severity_logger< logging::trivial::severity_level > lg;
};


extern std::shared_ptr<Engine> gameEngine;


#endif //SNEK_ENGINE_H
