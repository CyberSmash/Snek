//
// Created by jordan on 5/10/19.
//

#include "Food.h"

const wchar_t* FOOD_CHAR = L"@";

Food::Food(): GameObject(nullptr, 0, 0)
{
}

Food::Food(WINDOW *win, int y, int x) : GameObject(win, y, x)
{

}

void Food::Update()
{
    // Nothing to do here, really.
}

void Food::Draw()
{
    if (win == nullptr)
    {
        return;
    }

    mvwaddwstr(win, y, x, FOOD_CHAR);

}
