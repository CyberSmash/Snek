//
// Created by jordan on 5/8/19.
//

#include "Snake.h"
#include "Tag.h"

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

Snake::Snake(WINDOW* win, int y, int x, int length, Direction startDirection) :
    GameObject(win, y, x), direction(startDirection), oldDirection(startDirection),length(length)
{
    tag = Tag::PLAYER;
    for (int i = 0; i < length; i++)
    {

        Segment seg;
        // Handle the head special case.
        if (i == 0)
        {
            seg.isHead = true;
            seg.draw_chr = pickHeadCharacter();
            seg.y = y;
            seg.x = x;
            segments.push_back(seg);
            continue;
        }
        switch(startDirection)
        {
            case Direction::UP:
                seg.y = y - i;
                seg.x = x;
                break;
            case Direction::RIGHT:
                seg.y = y;
                seg.x = x - i;
                break;
            case Direction::DOWN:
                seg.y = y + i;
                seg.x = x;
                break;
            case Direction::LEFT:
                seg.y = y;
                seg.x = x + i;
                break;
        }

        seg.draw_chr = pickSegmentCharacter();
        segments.push_back(seg);
    }
}

/**
 * Force a direction change for this snake.
 *
 * @param direction The new direction.
 */
void Snake::setDirection(Direction newDirection)
{
    oldDirection = direction;
    direction = newDirection;

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
    if (isDead())
    {
        bool result = DeathAnimation();
        if (!result)
        {
            Destroy();
        }
        return;
    }

    if (eatingSelf() || outOfBounds())
    {
        kill();
        return;
    }
    processInput();
    struct Segment oldHead = segments.front();
    Segment newHead = {
            .isHead = true, // Currently Unused.
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

    segments.front().isHead = false;
    // This is a super inefficient way of doing this. It would be better to go through and update
    // each segments y,x values.
    segments.push_front(newHead);
    // Keep the same length, drop the last segment.
    // TODO: This will need to check for a food item, if that's the case,
    // we'll need to not drop the back segment, but let it stay for a single update.
    if (segmentsToAdd <= 0)
    {
        segments.pop_back();
    }
    else
    {
        segmentsToAdd--;
    }
}


/**
 * Get snake location x (column) value.
 *
 * @note: Always use this as opposed to the x value directly.
 *
 * @return The x locaton of the snake head.
 */
int Snake::getx()
{
    return segments.front().x;
}


/**
 * Get snake location y (row) value.
 *
 * @note: Always use this as opposed to the y value directly.
 *
 * @return The y location of the snake head.
 */
int Snake::gety()
{
    return segments.front().y;
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

void Snake::addSegments(int numSegments)
{
    segmentsToAdd = numSegments;
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
        default:
            return HEAD_LEFT;
    }
}

bool Snake::Collider(std::shared_ptr<GameObject> other)
{
    // TODO: Determine what happens if we hit another snake.
    if (other->getTag() == Tag::FOOD )
    {
        addSegments(1);
    }

    return false;
}

/**
 * Determine if the snake is eating itself.
 *
 * @note This could be handled in the collider, however, the collider only takes one point
 * of contact, and right now that's just the head. We could start re-working the code
 * to treat each segment of our snake's body as a game object in and of itself, but
 * maybe that's overkill? Maybe for another day.
 *
 * @return True if the snake is eating itself, False otherwise.
 */
bool Snake::eatingSelf()
{
    Segment head = segments.front();
    for (Segment seg : segments)
    {
        if (seg.isHead)
        {
            continue;
        }
        if (seg.y == head.y && seg.x == head.x)
        {
            return true;
        }

    }
    return false;
}

/**
 * Plays a simple animation where the snake slowly explodes over several frames, segment by segment.
 *
 * @return true if this animtion should continue for the next frame, false if it's finished.
 */
bool Snake::DeathAnimation()
{
    if (segments.empty())
    {
        return false;
    }

    // Grab the last segment, determine if it's character is a * or not
    int result = wcscmp(segments.back().draw_chr, L"*");

    if (result != 0)
    {
        // Last element hasn't been made a * yet, make it one
        segments.back().draw_chr = L"*";
    }
    else
    {
        // Remove from the list
        segments.pop_back();
    }
    return true;
}


/**
 * Determine if the snake is out of bounds.
 * @return True if we hit the wall, false otherwise.
 */
bool Snake::outOfBounds()
{
    int maxX = getmaxx(win);
    int maxY   getmaxy(win);

    return getx() <= 0 || getx() >= maxX - 1 || gety() <= 0 || gety() >= maxY - 1;
}
