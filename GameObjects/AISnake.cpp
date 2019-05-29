//
// Created by jordan on 5/26/19.
//
#include "Engine/Engine.h"
#include "AISnake.h"
#include <cmath>


AISnake::AISnake(WINDOW *win, int y, int x, int length, Direction startDirection) : Snake(win, y, x, length,
                                                                                          startDirection)
{

}


/**
 * Find the closest food item by calculating the distance.
 *
 * @note: if only one food item exists, we won't performa any calculation, and return
 * the only one.
 *
 * @param foods All of the foods in the play area.
 * @return The closest food item.
 */
std::shared_ptr<GameObject> AISnake::findClosest(std::list<std::shared_ptr<GameObject>> foods)
{
    if (foods.empty())
    {
        return nullptr;
    }
    if (foods.size() == 1)
    {
        return foods.front();
    }


    double minDistance = 100;
    shared_ptr<GameObject> selectedObject = nullptr;
    for (auto const &food : foods)
    {
        // Calculate distance.
        auto myX = static_cast<double>(getx());
        auto myY = static_cast<double>(gety());
        auto foodX = static_cast<double>(food->getx());
        auto foodY = static_cast<double>(food->gety());
        double distance = std::sqrt(std::pow(myX - foodX, 2) + std::pow(myY - foodY, 2));

        if (distance < minDistance || selectedObject == nullptr)
        {
            selectedObject = food;
            minDistance = distance;
        }

    }
    return selectedObject;
}

void AISnake::pickDirection()
{
    std::list<std::shared_ptr<GameObject>> food_game_objects = gameEngine->FindAllByTag(Tag::FOOD);
    if (food_game_objects.empty())
    {
        return;
    }

    std::shared_ptr<GameObject> closestFood = findClosest(food_game_objects);

    std::shared_ptr<Food> food = std::dynamic_pointer_cast<Food>(food_game_objects.front());
    if (food == nullptr)
    {
        // TODO: I really do need some method of logging.
        return;
    }

    std::vector<Direction> possibleDirections = directionsAvailable();
    if (possibleDirections.empty())
    {
        // I guess we're stuck. Continue this direction.
        return;
    }


    // I'm not convinced that this code really works.
    auto tmp_it = std::find(possibleDirections.begin(), possibleDirections.end(), direction);
    if (tmp_it == possibleDirections.end())
    {
        // Our current direction is no longer available.
        if (possibleDirections.size() == 2)
        {
            if (isConcave(possibleDirections[0]) && !isConcave(possibleDirections[1]))
            {
                setDirection(possibleDirections[1]);
            }
            else if (!isConcave(possibleDirections[0]) && isConcave(possibleDirections[1]))
            {
                setDirection(possibleDirections[0]);
            }
        }
    }

    Direction desiredXDirection = getDesiredXDirection(closestFood);
    Direction desiredYDirection = getDesiredYDirection(closestFood);

    if (desiredXDirection == Direction::NONE && desiredYDirection == Direction::NONE)
    {
        // This isn't really possible, but if it is, just take the first available direction.
        setDirection(possibleDirections.front());
        return;
    }

    // Determine if the desired X or Y directions are available. Make the first one found our choice.
    if (desiredXDirection != Direction::NONE)
    {
        // Ensure we can / want to even move in this way.
        auto it = std::find(possibleDirections.begin(), possibleDirections.end(), desiredXDirection);
        if (it != possibleDirections.end())
        {
            setDirection(desiredXDirection);
            return;
        }
    }

    // NB: We don't want an if else here, because we could have failed our find check above.
    if (desiredYDirection != Direction::NONE)
    {
        auto it = std::find(possibleDirections.begin(), possibleDirections.end(), desiredYDirection);
        if (it != possibleDirections.end())
        {
            setDirection(desiredYDirection);
            return;
        }
    }

    // At this point we can't make progress with either our desired X or desired Y directions, simply take
    // the first available.
    setDirection(possibleDirections.front());

}

/**
 * Attempt to calculate a desireable direction that we would want to move in if we could
 *
 * @note: This only is the desireable X direction to move in, if one was possible, This doesn't determine
 * if it's possible.
 *
 * @param closestFood The closest food around.
 * @retval Direction::NONE if we are already on the same level.
 * @retval Direction::LEFT if we would want to increase our X value.
 * @retval Direction::RIGHT if we want to decrease our X value.
 */
Direction AISnake::getDesiredXDirection(std::shared_ptr<GameObject> closestFood)
{
    int xDistance = getx() - closestFood->getx();

    if (xDistance == 0)
    {
        // We already have the x direction nailed.
        return Direction::NONE;
    }
    else if (xDistance > 0)
    {
        // Food is to the left
        return Direction::LEFT;
    }
    else
    {
        // Food is to the right.
        return Direction::RIGHT;
    }
}


/**
 * Attempt to calculate a desireable direction that we would want to move in if we could
 *
 * @note: This only is the desireable Y direction to move in, if one was possble, This doesn't determine
 * if it's possible.
 *
 * @param closestFood The closest food around.
 * @retval Direction::NONE if we are already on the same level.
 * @retval Direction::UP if we would want to decrease our Y value.
 * @retval Direction::DOWN if we want to increase our Y value.
 */
Direction AISnake::getDesiredYDirection(std::shared_ptr<GameObject> const closestFood)
{
    int y_distance = gety() - closestFood->gety();
    if (y_distance == 0)
    {
        // We already have the y direction nailed.
        return Direction::NONE;
    }
    else if (y_distance > 0)
    {
        // Food is up
        return Direction::UP;
    }
    else
    {
        // Food is down.
        return Direction::DOWN;
    }

}

/**
 * Given a chosen direction, determine if that choice would be turning into a concave alcove, or convex.
 *
 * This code is a bit confusing, but effectively if I am going to turn a direction I want to check that I am not
 * turning into other segments, and preferably turn away from them. That is all the lambda ultimately checks.
 *
 * @param chosenDirection The direction you would turn towards
 * @return True if the turn would be a concave turn (bad) false if it is convex (good).
 */
bool AISnake::isConcave(Direction chosenDirection)
{
    int maxx = 0;
    int maxy = 0;

    getmaxyx(win, maxy, maxx);

    int nexty = gety();
    int nextx = getx();

    auto it = segments.begin();
    if (chosenDirection == Direction::RIGHT)
    {
        // Check if there are any other segments to our in the whole screen
        it = std::find_if(segments.begin(), segments.end(), [nexty, nextx](const Segment& seg) {
            return seg.y == nexty && seg.x > nextx;
        });

    }
    else if (chosenDirection == Direction::LEFT)
    {
        it = std::find_if(segments.begin(), segments.end(), [nexty, nextx](const Segment &seg) {
            return seg.y == nexty && seg.x < nextx;
        });
    }

    else if (chosenDirection == Direction::UP)
    {
        it = std::find_if(segments.begin(), segments.end(), [nexty, nextx](const Segment &seg) {
            return seg.x == nextx && seg.y < nexty;
        });
    }
    else if (chosenDirection == Direction::DOWN)
    {
        it = std::find_if(segments.begin(), segments.end(), [nexty, nextx](const Segment &seg) {
            return seg.x == nextx && seg.y > nexty;
        });
    }
    else
    {
        throw std::runtime_error("Unknown direction chosen for concavity.");
    }

    return it != segments.end();

}


/**
 * Get all available directions we can turn that do not cause us to run into ourselves or go out of bounds.
 *
 * @return A vector containing all of the directions we can turn.l
 */
std::vector<Direction> AISnake::directionsAvailable()
{
    // TODO: check for the edge of the screen
    std::vector<Direction> available;

    // Get the game area bounds.
    // TODO: This might not account for what to do if we have different shaped "maps" However, I think
    // in that case, we wont use "box()" but we'll actually draw walls as game objects.
    int minx = 0;
    int miny = 0;
    int maxy = getmaxy(win);
    int maxx = getmaxx(win);

    Segment head = segments.front();

    // Can we go up?
    if (direction != Direction::DOWN
        && head.y - 1 > miny
        && !segmentExistsAt(head.y - 1, head.x))
    {
        available.push_back(Direction::UP);
    }

    // Can we go down?
    if (direction != Direction::UP
        && head.y + 1 < maxy - 1
        && !segmentExistsAt(head.y + 1, head.x))
    {
        available.push_back(Direction::DOWN);
    }

    // Can we go left?
    if (
        direction != Direction::RIGHT
        && head.x - 1 > minx
        && !segmentExistsAt(head.y, head.x - 1))
    {
        available.push_back(Direction::LEFT);
    }

    // Can we go right?
    if (direction != Direction::LEFT
    && head.x + 1 < maxx - 1
    && !segmentExistsAt(head.y, head.x + 1))
    {
        available.push_back(Direction::RIGHT);
    }

    return available;
}

/**
 * Determine if a segment exists at a give coordinate.
 * @param y The y coordinate in relation to the current window
 * @param x The x coordinate in relation to the current window
 * @return True if there is a segment at that location, false otherwise.
 */
bool AISnake::segmentExistsAt(int y, int x)
{
    for (auto segment : segments)
    {

        if (segment.y == y && segment.x == x)
        {
            return true;
        }
    }
    return false;
}

/**
 * Our main update function.
 */
void AISnake::Update()
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
    pickDirection();
    struct Segment oldHead = segments.front();
    Segment newHead = {
            .isHead = true,
            .y = oldHead.y,
            .x = oldHead.x,
            .draw_chr = HORIZONTAL,
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
