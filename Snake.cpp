//
// Created by jordan on 5/8/19.
//

#include "Snake.h"

//#define HEAD_CHAR L'@'
//#define SEGMENT_CHAR L'm'

const wchar_t* VERTICAL = L"\u2502";
const wchar_t* HORIZONTAL = L"\u2500";
const wchar_t* UP_RIGHT_ELBOW = L"\u256d";
const wchar_t* UP_LEFT_ELBOW = L"\u256e";
const wchar_t* DOWN_RIGHT_ELBOW = L"\u2514";
const wchar_t* DOWN_LEFT_ELBOW = L"\u2518";
const wchar_t* RIGHT_DOWN_ELBOW = L"\u256e";
const wchar_t* LEFT_DOWN_ELBOW = L"\u256d";
const wchar_t* RIGHT_UP_ELBOW = L"\u2518";
const wchar_t* LEFT_UP_ELBOW = L"\u2514";

const wchar_t* HEAD_LEFT = L"\u2578";
const wchar_t* HEAD_TOP = L"\u2579";
const wchar_t* HEAD_RIGHT = L"\u257A";
const wchar_t* HEAD_BOTTOM = L"\u257B";

Snake::Snake(WINDOW *win, int y, int x, int length, Direction startDirection) :
    GameObject(win, y, x), length(length), direction(startDirection), oldDirection(startDirection)
{
    for (int i = 0; i < length; i++)
    {
        Segment seg;
        seg.x = x + i;
        seg.y = y;
        if (startDirection == Direction::LEFT || startDirection == Direction::RIGHT)
        {
            seg.draw_chr = HORIZONTAL;
        }
        else
        {
            seg.draw_chr = VERTICAL;
        }
        segments.push_back(seg);
    }
}

/**
 * Force a direction change for this snake.
 *
 * @param direction The new direction.
 */
void Snake::setDirection(Direction direction)
{
    this->oldDirection = this->direction;
    this->direction = direction;

}

/**
 * Determine the current direction of the snake.
 *
 * @return A direction.
 */
Direction Snake::getDirection()
{
    return this->direction;
}

/**
 * Main "Step" function.
 *
 * This will check for any input from our input router, and then set up our snake data object
 * to the appropriate values.
 */
void Snake::Update()
{
    processInput();
    struct Segment oldHead = segments.front();
    Segment newHead = {
            .ishead = false, // Currently Unused.
            .y = oldHead.y,
            .x = oldHead.x,
            .draw_chr = HORIZONTAL, // Currently unused.
    };

    switch(direction)
    {
        case Direction::RIGHT:
            newHead.x += 1;
            newHead.draw_chr = pickHeadCharacter();
            break;
        case Direction::LEFT:
            newHead.x -= 1;
            newHead.draw_chr = pickHeadCharacter();
            break;
        case Direction::UP:
            newHead.y -= 1;
            newHead.draw_chr = pickHeadCharacter();
            break;
        case Direction::DOWN:
            newHead.y += 1;
            newHead.draw_chr = pickHeadCharacter();
            break;
        default:
            break;
    }
    if (direction != oldDirection)
    {
        // Get the first in the list, change its draw chr. appropriately.
        segments.front().draw_chr = pickSegmentCharacter();
    }
    else
    {
        if (direction == Direction::LEFT || direction == Direction::RIGHT)
        {
            segments.front().draw_chr = HORIZONTAL;
        }
        if (direction == Direction::UP || direction == Direction::DOWN)
        {
            segments.front().draw_chr = VERTICAL;
        }

    }
    segments.push_front(newHead);
    // Keep the same length, drop the last segment.
    // TODO: This will need to check for a food item, if that's the case,
    // we'll need to not drop the back segment, but let it stay for a single update.
    segments.pop_back();
}

/**
 * Draw The snake
 *
 * Draws the snake to th screen. There are 3 parts to this:
 * 1. Calculate the segments that aren't elbows
 * 2. Calculate the elbows
 * 3. Calculate the head direction.
 */
void Snake::Draw()
{
    // Ensure we actually have a window to draw to.
    if (win == nullptr)
    {
        // TODO: Figure out how to alert the user to a problem.
        return;
    }
    for (auto it = segments.begin(); it != segments.end(); it++)
    {
        if (it == segments.begin())
        {
            mvwaddwstr(this->win, it->y, it->x, it->draw_chr);
            continue;
        }
        // Start at the head.
        mvwaddwstr(this->win, it->y, it->x, it->draw_chr);
    }
}

/**
 * Determine if the snake is dead.
 * @return
 */
bool Snake::isDead()
{
    return this->dead;
}

/**
 * Kill the snake.
 */
void Snake::kill()
{
    this->dead = true;
}

/**
 * Process input from our router.
 *
 * Also returns the input incase the rest of the caller needs it for any reason.
 *
 * @return The input. ERR if none is available.
 */
int Snake::processInput()
{
    int input = inputRouter.getInput();

    // TODO: Does a switch statement really still make sense here? Maybe a carefull crafted if.
    switch(input)
    {
        case ERR:
            this->oldDirection = this->direction;
            break;
        case KEY_UP:
            if (this->direction != Direction::DOWN)
            {
                this->oldDirection = this->direction;
                this->direction = Direction::UP;
            }
            break;
        case KEY_DOWN:
            if (this->direction != Direction::UP)
            {
                this->oldDirection = this->direction;
                this->direction = Direction::DOWN;
            }
            break;
        case KEY_LEFT:
            if (this->direction != Direction::RIGHT)
            {
                this->oldDirection = direction;
                this->direction = Direction::LEFT;
            }
            break;
        case KEY_RIGHT:
            if (this->direction != Direction::LEFT)
            {
                this->oldDirection = direction;
                this->direction = Direction::RIGHT;
            }
            break;
        default:
            break;
    }

    return input;
}

/**
 * Pick the segement character for turns.
 *
 * This will determine what direction we are turning to, and what direction we
 * turned from, and pick the appropriate segment character to display to the user.
 *
 * TODO: Consider refactoring this a bit. Not sure how easily it reads.
 *
 * @return A character to display for this particular segment.
 */
const wchar_t* Snake::pickSegmentCharacter()
{
    // When we are heading to the right.
    if (direction == Direction::RIGHT)
    {
        if (oldDirection == direction)
        {
            return HORIZONTAL;
        }
        else if (oldDirection == Direction::DOWN)
        {
            return DOWN_RIGHT_ELBOW;
        }
        else if (oldDirection == Direction::UP)
        {
            return UP_RIGHT_ELBOW;
        }

    }
    if (direction == Direction::LEFT)
    {
        if (oldDirection != direction && oldDirection == Direction::DOWN)
        {
            return DOWN_LEFT_ELBOW;
        }
        else if (oldDirection != direction && oldDirection == Direction::UP)
        {
            return UP_LEFT_ELBOW;
        }
        else
        {
            return HORIZONTAL;
        }
    }


    if (direction == Direction::DOWN)
    {
        if (oldDirection == direction)
        {
            return HORIZONTAL;
        }
        else if (oldDirection == Direction::LEFT)
        {
            return LEFT_DOWN_ELBOW;
        }
        else if (oldDirection == Direction::RIGHT)
        {
            return RIGHT_DOWN_ELBOW;
        }

    }

    if (direction == Direction::UP)
    {
        if (oldDirection == direction)
        {
            return VERTICAL;
        }
        else if (oldDirection == Direction::LEFT)
        {
            return LEFT_UP_ELBOW;
        }
        else if (oldDirection == Direction::RIGHT)
        {
            return RIGHT_UP_ELBOW;
        }
    }

    return VERTICAL;

}

/**
 * Pick the head character.
 *
 * This chacter only goes half way across the cell.
 *
 * @return The character to use.
 */
const wchar_t* Snake::pickHeadCharacter()
{
    switch(direction)
    {
        case Direction::UP:
            return HEAD_BOTTOM;
        case Direction::DOWN:
            return HEAD_TOP;
        case Direction::LEFT:
            return HEAD_RIGHT;
        case Direction::RIGHT:
            return HEAD_LEFT;
    }
}