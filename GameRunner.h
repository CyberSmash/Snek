//
// Created by jordan on 5/18/19.
//

#ifndef SNEK_GAMERUNNER_H
#define SNEK_GAMERUNNER_H
#include <list>
#include <memory>
#include <ncurses.h>
#include "GameObject.h"
#include "Snake.h"
#include "Food.h"

class GameRunner : public GameObject
{
public:
    GameRunner(WINDOW* win);
    ~GameRunner() override = default;

    void Update()   override;
    void Draw()     override;

    void setPlayers(std::list<std::shared_ptr<Snake>> newPlayers);
    std::list<std::shared_ptr<Snake>> getPlayers();

    void addPlayer(std::shared_ptr<Snake> player);
    void removePlayer(std::shared_ptr<Snake> const &player);




protected:
    int             numPlayers   {1};
    unsigned int    numFood      {1};

    std::list<std::shared_ptr<Snake>> players {};
    std::list<std::shared_ptr<Food>> food {};


private:
    void addRandomFood();
};


#endif //SNEK_GAMERUNNER_H
