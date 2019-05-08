//
// Created by jordan on 5/8/19.
//

#include "Snake.h"

Snake::Snake(WINDOW *win, int y, int x, int length, Direction startDirection) :
    GameObject(win, y, x), length(length), direction(startDirection)
{

}

void Snake::setDirection(Direction direction)
{
    this->direction = direction;
}

Direction Snake::getDirection()
{
    return this->direction;
}

void Snake::Update()
{
    processInput();
    struct Segment oldHead = segments.front();
    struct Segment newHead;
    newHead.y = oldHead.y;
    newHead.x = oldHead.x;

    switch(direction)
    {
        case Direction::RIGHT:
            newHead.x += 1;
            break;
        case Direction::LEFT:
            newHead.x -= 1;
            break;
        case Direction::UP:
            newHead.y -= 1;
            break;
        case Direction::DOWN:
            newHead.y += 1;
            break;
        default:
            break;
    }

    segments.push_front(newHead);
    // Keep the same length, drop the last segment.
    // TODO: This will need to check for a food item, if that's the case,
    // we'll need to not drop the back segment, but let it stay for a single update.
    segments.pop_back();
}

void Snake::Draw()
{

}

bool Snake::isDead()
{
    return this->dead;
}

void Snake::kill()
{
    this->dead = true;
}

int Snake::processInput()
{
    int input = inputRouter.getInput();

    switch(input)
    {
        case ERR:
            break;
        case KEY_UP:
            if (this->direction != Direction::DOWN)
                this->direction = Direction::UP;
            break;
        case KEY_DOWN:
            if (this->direction != Direction::UP)
                this->direction = Direction::DOWN;
            break;
        case KEY_LEFT:
            if (this->direction != Direction::RIGHT)
                this->direction = Direction::LEFT;
            break;
        case KEY_RIGHT:
            if (this->direction != Direction::LEFT)
                this->direction = Direction::RIGHT;
            break;
        default:
            break;
    }

    return input;
}
