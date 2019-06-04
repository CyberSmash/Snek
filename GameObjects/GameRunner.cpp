//
// Created by jordan on 5/18/19.
//

#include  <random>
#include <time.h>
#include <ncurses.h>
#include <algorithm>
#include "GameRunner.h"
#include "Engine/Engine.h"
#include "Engine/Tag.h"
#include "Engine/AudioEngine.h"
#include "AudioController.h"
#include "GameObjects/Snake.h"

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
}


void GameRunner::Start()
{
    std::list<std::shared_ptr<ScoreBoard>> scoreBoards = gameEngine->FindGOByType<ScoreBoard>();
    if (scoreBoards.empty())
    {
        throw std::logic_error("You must have at least one scoreboard game object.");
    }
    scoreBoard = scoreBoards.front();
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
    int key = gameEngine->getInput();
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
    box(win, 0, 0);
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

void GameRunner::foodEaten(std::shared_ptr<Food> const eatenFood)
{
    scoreBoard->IncreaseScore(eatenFood->getScore());
}
