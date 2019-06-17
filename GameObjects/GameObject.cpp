//
// Created by jordan on 5/8/19.
//

#include "GameObject.h"

GameObject::GameObject() // x and y have already been set to default values.
{

}

GameObject::GameObject(WINDOW *gameWin, int y, int x) : y(y), x(x), win(gameWin)
{

}

void GameObject::Start()
{

}

void GameObject::Draw()
{

}

void GameObject::Update()
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

void GameObject::Destroy()
{
    destroy = true;
}

Tag GameObject::getTag()
{
    return tag;
}

void GameObject::setTag(Tag newTag)
{
    tag = newTag;
}

bool GameObject::Collider(GameObjectSptr other)
{
    return false;
}

bool GameObject::isDestroyed()
{
    return destroy;
}
