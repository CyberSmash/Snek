//
// Created by jordan on 5/10/19.
//

//#define _XOPEN_SOURCE_EXTENDED
#include "Food.h"
#include "Engine/AudioEngine.h"
#include <ncurses.h>
#include <stdio.h>
#include <memory>
const wchar_t* FOOD_CHAR = L"\u2638";

Food::Food(WINDOW* foodwin, int y, int x) : GameObject(foodwin, y, x)
{
    tag = Tag::FOOD;
}

void Food::Update()
{
    // Nothing to do here, really.

}

void Food::Draw()
{
    mvwaddwstr(win, y, x, FOOD_CHAR);
}


/**
 *
 * @param go
 * @return
 */
bool Food::Collider(GameObjectSptr other)
{
    if (other->getTag() == Tag::PLAYER)
    {
        audioEngine->PlaySound(AudioTag::EAT_FOOD);
        Destroy();
    }
    return true;
}

/**
 * Get the number of segments the player should be given.
 *
 * @return The number of segments to add to the players size.
 */
int Food::getSegmentValue()
{
    return segmentValue;
}

/**
 * Get the value of this food item.
 *
 * @return The score that the player should be given.
 */
int Food::getScore()
{
    return score;
}
