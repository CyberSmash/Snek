//
// Created by jordan on 5/10/19.
//

//#define _XOPEN_SOURCE_EXTENDED
#include "Food.h"
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
bool Food::Collider(std::shared_ptr<GameObject> other)
{
    if (other->getTag() == Tag::PLAYER)
    {
        Destroy();
    }
    return true;
}