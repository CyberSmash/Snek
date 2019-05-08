//
// Created by jordan on 5/8/19.
//

#include "GameObject.h"

GameObject::GameObject(WINDOW *win, int y, int x) : win(win), x(x), y(y)
{

}

void GameObject::setWin(WINDOW *newWin)
{
    this->win = newWin;
}

WINDOW *GameObject::getWin()
{
    return this->win;
}

void GameObject::setyx(int newY, int newX)
{
    this->x = newX;
    this->y = newY;
}

void GameObject::sety(int newY)
{
    this->y = newY;
}

void GameObject::setx(int newX)
{
    this->x = newX;
}

int GameObject::gety()
{
    return this->y;
}

int GameObject::getx()
{
    return this->x;
}
