//
// Created by jordan on 5/8/19.
//

#ifndef SNEK_SNAKE_H
#define SNEK_SNAKE_H

#include "GameObject.h"
#include "InputRouter.h"
#include "defns.h"
#include <list>


/**
 * TODO: I need to figure out a better way to store these variables.
 */
extern const wchar_t* VERTICAL;
extern const wchar_t* HORIZONTAL;
extern const wchar_t* UP_RIGHT_ELBOW;
extern const wchar_t* UP_LEFT_ELBOW;
extern const wchar_t* DOWN_RIGHT_ELBOW;
extern const wchar_t* DOWN_LEFT_ELBOW;
extern const wchar_t* RIGHT_DOWN_ELBOW;
extern const wchar_t* LEFT_DOWN_ELBOW;
extern const wchar_t* RIGHT_UP_ELBOW;
extern const wchar_t* LEFT_UP_ELBOW;

extern const wchar_t* HEAD_LEFT;
extern const wchar_t* HEAD_TOP;
extern const wchar_t* HEAD_RIGHT;
extern const wchar_t* HEAD_BOTTOM;

// TODO: Remove this and clean it up, maybe typedef out the std::list<std::shared_ptr<GameObject>>

struct Segment
{
    bool isHead {false};
    int y {0};
    int x {0};
    const wchar_t* draw_chr {HEAD_BOTTOM};
};

class Snake : public GameObject
{
public:
    Snake(WINDOW* win, int y, int x, int length, Direction startDirection);

    // Set and get the direction
    void setDirection(Direction direction);
    Direction getDirection();

    void Update() override;
    void Draw() override;

    // Determine or set whether or not the snake is dead.
    bool isDead();
    void kill();

    int getx() override;
    int gety() override;

    int getLength() { return segments.size(); }

    void addSegments(int numSegments);
    bool Collider(std::shared_ptr<GameObject> other) override;
private:

    bool DeathAnimation();
    bool eatingSelf();
    int processInput();
    const wchar_t* pickSegmentCharacter();
    const wchar_t* pickHeadCharacter();

    std::list<Segment>  segments      {};
    Direction           direction     {Direction::UP};
    Direction           oldDirection  {Direction::UP};
    bool                dead          {false};
    int                 length        {0};
    InputRouter         inputRouter   {};
    int                 segmentsToAdd {0};
};


#endif //SNEK_SNAKE_H
