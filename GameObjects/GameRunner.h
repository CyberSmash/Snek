//
// Created by jordan on 5/18/19.
//

#ifndef SNEK_GAMERUNNER_H
#define SNEK_GAMERUNNER_H

class Snake;
class ScoreBoard;

#include <list>
#include <memory>
#include <ncurses.h>
#include "GameObject.h"
#include "Food.h"
#include "ScoreBoard.h"


class GameRunner : public GameObject
{
public:
    GameRunner(WINDOW* win);
    ~GameRunner() override = default;

    void Start()    override;
    void Update()   override;
    void Draw()     override;

    void setPlayers(std::list<std::shared_ptr<Snake>> newPlayers);
    std::list<std::shared_ptr<Snake>> getPlayers();

    void addPlayer(std::shared_ptr<Snake> player);
    void removePlayer(std::shared_ptr<Snake> const &player);

    void setNumFood(unsigned int newNum);

    void foodEaten(std::shared_ptr<Food> const eatenFood);

protected:
    int             numPlayers   {1};
    unsigned int    numFood      {1};

    std::list<std::shared_ptr<Snake>> players {};
    std::list<std::shared_ptr<Food>> food {};
    std::shared_ptr<ScoreBoard> scoreBoard {nullptr};

private:
    void addRandomFood();
};


#endif //SNEK_GAMERUNNER_H
