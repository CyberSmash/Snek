//
// Created by jordan on 5/8/19.
//

#ifndef SNEK_SNAKE_H
#define SNEK_SNAKE_H

#include "GameObject.h"
#include "InputRouter.h"
#include "defns.h"
#include <list>


using std::list;

struct Segment
{
    bool ishead;
    int y;
    int x;
    const wchar_t* draw_chr;
};

class Snake : public GameObject
{
public:
    Snake(WINDOW* win, int y, int x, int length, Direction startDirection);

    // Set and get the direction
    void setDirection(Direction direction);
    Direction getDirection();

    void Update();
    void Draw();

    // Determine or set whether or not the snake is dead.
    bool isDead();
    void kill();

    int getLength() { return segments.size(); }

private:

    int processInput();
    const wchar_t* pickSegmentCharacter();
    const wchar_t* pickHeadCharacter();

    list<Segment> segments;
    Direction direction;
    Direction oldDirection;
    bool dead = false;
    int length;
    InputRouter inputRouter;
};


#endif //SNEK_SNAKE_H
