//
// Created by jordan on 5/26/19.
//

#ifndef SNEK_AISNAKE_H
#define SNEK_AISNAKE_H


#include "Snake.h"

class AISnake : public Snake
{
public:
    AISnake(WINDOW* win, int y, int x, int length, Direction startDirection);
    void Update() override;


protected:
    void pickDirection();
    Direction getDesiredXDirection(GameObjectSptr closestFood);
    Direction getDesiredYDirection(GameObjectSptr closestFood);
    vector<Direction> directionsAvailable();
    bool segmentExistsAt(int y, int x);
    bool isConcave(Direction chosenDirection);
    GameObjectSptr findClosest(std::list<GameObjectSptr> foods);

};


#endif //SNEK_AISNAKE_H
