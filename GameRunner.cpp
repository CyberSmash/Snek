//
// Created by jordan on 5/18/19.
//

#include  <random>
#include <time.h>
#include <ncurses.h>
#include <algorithm>
#include "GameRunner.h"
#include "Engine.h"
#include "Tag.h"

/**
 * Constructor
 *
 * No need to do anything here. We are not going to draw this
 * object.
 */
GameRunner::GameRunner(WINDOW * gameWindow) : GameObject(gameWindow, 0, 0)
{
    // TODO: Does it matter if I ever replace this with something that's actually random? Probably not.
    srand(time(nullptr));
    // Get our player objects from the game engine.
    // TODO: Doing this once isn't that bad on the engine. However, maybe we should search by tag.
    players = gameEngine->FindGOByType<Snake>();

    // Get any existing Food objects from the engine.
    food = gameEngine->FindGOByType<Food>();

    input = std::make_unique<InputRouter>();
    input->setWindow(stdscr);
}


/**
 * Update The Game object.
 *
 * All of our game logic step-by-step will go here.
 */
void GameRunner::Update()
{
    // Determine how many food items are still around
    std::list<std::shared_ptr<GameObject>> foodItems = gameEngine->FindAllByTag(Tag::FOOD);

    for (unsigned int i = foodItems.size(); i < numFood; i++)
    {
            addRandomFood();
    }
    //input->checkInput();
    int key = input->getInput();
    if (key == 'f')
    {
        numFood += 1;
    }


}

/**
 * Add food to the game at a random location
 *
 * TODO: Could still put food on the tail of a snake.
 */
void GameRunner::addRandomFood()
{

    int maxy = getmaxy(win);
    int maxx = getmaxx(win);
    int y = 0;
    int x = 0;
    do {
        // TODO: I'm Pretty sure this unfairly biases the lower number "1" because 0 is also 1 when clamped.
        y = std::clamp(rand() % maxy - 1, 1, maxy - 1);
        x = std::clamp(rand() % maxx - 1, 1, maxx - 1);
    } while (gameEngine->gameObjectAtLocation(y, x));
    gameEngine->addGameObject(std::make_shared<Food>(win, y, x));

}

/**
 * Draw the game object.
 *
 * We will not use this as this game object only manages the game.
 */
void GameRunner::Draw()
{
    // This object will not be drawn, it just controls our game state.
}


/**
 * Set up all of the players in the game in one swoop.
 *
 * @param newPlayers The players to add.
 */
void GameRunner::setPlayers(std::list<std::shared_ptr<Snake>> newPlayers)
{
    players = std::move(newPlayers);
}


/**
 * Get the list of players to the game.
 *
 * @return a list of players.
 */
std::list<std::shared_ptr<Snake>> GameRunner::getPlayers()
{
    return players;
}


/**
 * Add a player to the list of players we are watching.
 *
 * @param player The player to add.
 */
void GameRunner::addPlayer(std::shared_ptr<Snake> player)
{
    players.emplace_back(std::move(player));
}


/**
 * Remove a player object from our list of players.
 *
 * @param player A shared pointer to the player to remove.
 */
void GameRunner::removePlayer(std::shared_ptr<Snake> const &player)
{
    for (auto it = players.begin(); it != players.end(); it++)
    {
        if (*it == player)
        {
            players.erase(it);
            return;
        }
    }
}

void GameRunner::setNumFood(unsigned int newNum)
{
    numFood = newNum;
}