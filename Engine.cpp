//
// Created by jordan on 5/10/19.
//

#include "Engine.h"

Engine::Engine() : numPlayers(0), win(nullptr)
{
}

Engine::Engine(WINDOW *gameWindow, int players) : win(gameWindow), numPlayers(players)
{
    if (numPlayers == 0)
    {
        return;
    }
    for (int i = 0; i < numPlayers; i++)
    {
        // TODO: Change start location.
        gameObjects.push_back(Snake(win, 5, 5, 5, Direction::RIGHT));
    }
}

void Engine::Begin()
{
    // Do anything we need to then start the main loop.
    MainLoop();
}

void Engine::MainLoop()
{
    // Do anything we need to, then end the game.
    End();
}

void Engine::End()
{

}
