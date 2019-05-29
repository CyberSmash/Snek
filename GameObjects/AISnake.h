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
    Direction getDesiredXDirection(std::shared_ptr<GameObject> closestFood);
    Direction getDesiredYDirection(std::shared_ptr<GameObject> closestFood);
    vector<Direction> directionsAvailable();
    bool segmentExistsAt(int y, int x);
    bool isConcave(Direction chosenDirection);
    std::shared_ptr<GameObject> findClosest(std::list<std::shared_ptr<GameObject>> foods);

};


#endif //SNEK_AISNAKE_H
