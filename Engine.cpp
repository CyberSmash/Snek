//
// Created by jordan on 5/10/19.
//

#include "Engine.h"
#include "algorithm"
#include <thread>
#include <chrono>


#define LOOP_SLEEP_MS 200

Engine::Engine() : numPlayers(0), win(nullptr)
{
}

Engine::Engine(WINDOW *gameWindow, int players) : numPlayers(players), win(gameWindow)
{
    inputRouter = std::make_unique<InputRouter>();
    inputRouter->setWindow(stdscr);
    if (numPlayers == 0)
    {
        return;
    }
    for (int i = 0; i < numPlayers; i++)
    {
        // TODO: Change start location and size.
        gameObjects.emplace_back(std::make_shared<Snake>(win, 5, 5, 5, Direction::RIGHT));
    }
}

void Engine::Begin()
{
    // Do anything we need to then start the main loop.
    state = GameState::MAIN;
}

void Engine::MainLoop()
{
    // Do anything we need to, then end the game.
    int input = ERR;

    while(input != 'q')
    {

        werase(win);
        inputRouter->checkInput();
        input = inputRouter->getInput();
        box(win, 0, 0);

        for (shared_ptr<GameObject> go : gameObjects)
        {
            // Move the game forward
            go->Update();

            // Draw the game state.
            go->Draw();

        }
        processCollisions();
        processDestroyed();

        wrefresh(win);
        std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_SLEEP_MS));

        // Sleep to provide a framerate.

    }
    state = GameState::END;
}

void Engine::processCollisions()
{
    // auto const &go syntax is weird. Essentially I'm telling the compiler
    // That I don't want to make any changes or copies.
    // auto x - Works with copies
    // auto &x - Work with original, but I might make changes
    // auto const &x - Work with original, with no changes.
    for (auto const &go : gameObjects)
    {
        for ( auto const &other : gameObjects)
        {
            if (go == other)
            {
                continue;
            }
            if (go->getx() == other->getx() && go->gety() == other->gety())
            {
                go->Collider(other);
            }
        }
    }
}

void Engine::processDestroyed()
{
    for (auto it = gameObjects.begin(); it != gameObjects.end();)
    {
        shared_ptr<GameObject> tmp = *it;
        if (tmp->isDestroyed())
        {
            it = gameObjects.erase(it);
            continue;
        }
        it++;
    }
}

void Engine::End()
{
}

void Engine::RunGame()
{

    switch(state)
    {
        case GameState::BEGIN:
            Begin();
            break;
        case GameState::MAIN:
            MainLoop();
            break;
        case GameState::END:
            End();
            break;
        default:
            break;
    }
}

void Engine::addGameObject(shared_ptr<GameObject> go)
{
    if (go == nullptr)
    {
        return;
    }

    auto it = std::find(std::begin(gameObjects), std::end(gameObjects), go);
    if (it != std::end(gameObjects))
    {
        // We found our game object already in or list. Don't add it.
        // TODO: Is there any real reason to return a value here?
        return;
    }

    gameObjects.emplace_back(go);
}

int Engine::numGameObjects()
{
    return gameObjects.size();
}

bool Engine::areAnyDead()
{

    list<shared_ptr<Snake>> snakes = FindGOByType<Snake>();
    for (auto snake : snakes)
    {
        if (snake->isDead())
        {
            return true;
        }
    }
    // If there are no snakes, i guess they're all dead.
    return true;

}

/**
 * Get all game objects of  specific type.
 *
 * This works similar to Unity's Find() function.
 *
 * @note This function is likely pretty bad performance wise.
 * This is due to the fact that the application has to check the RTTI table
 * each time, and determine if the cast is valid. Then we have to check
 * the return alue of the dynamic cast. All in all, it's probably better
 * to find the game object by the tag, but this can be useful.
 *
 * @tparam T The type of object to find.
 * @return A list of all of the objects matching the type.
 */
template<typename T>
list<shared_ptr<T>> Engine::FindGOByType()
{
    list<shared_ptr<T>> l;
    // I could use auto here. However, I don't like doing that unless the type is
    // difficult to predict (such as with iterators) or if the actual type isn't somewhere
    // nearby.
    for (shared_ptr<GameObject> go : gameObjects)
    {
        // Downcast the pointer. If the downcast fails, then nullptr will be returned, and
        // the object isn't the one we want.
        shared_ptr<T> tmp = std::dynamic_pointer_cast<T>(go);
        if (tmp != nullptr)
        {
            l.emplace_back(tmp);
        }
    }
    return l;
}

/**
 * Determine if this type is the same as the suggested one.
 *
 * @tparam T - The type that you are comparing against.
 * @param go - The game object in queston.
 * @return True if the the type is the same.
 */
template <typename T>
bool Engine::isType(shared_ptr<GameObject> go)
{
    shared_ptr<T> tmp = std::dynamic_pointer_cast<T>(go);
    return tmp != nullptr;
}


template class list<shared_ptr<GameObject>> Engine::FindGOByType<GameObject>();
template class list<shared_ptr<Snake>> Engine::FindGOByType<Snake>();
template class list<shared_ptr<Food>> Engine::FindGOByType<Food>();


